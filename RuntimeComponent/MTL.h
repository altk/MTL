#pragma once
#include <Windows.h>
#include <inspectable.h>
#include <type_traits>
#include <activation.h>
#include <new>
#include <string.h>
#include <ObjIdlbase.h>

namespace MTL
{
#pragma region Cloaked traits
	template <typename Interface>
	struct Cloaked : Interface
	{
	};

	template <typename Interface>
	struct IsCloaked : std::false_type
	{
	};

	template <typename Interface>
	struct IsCloaked<Cloaked<Interface>> : std::true_type
	{
	};
#pragma endregion

#pragma region Static ckecks
	template <typename Interface>
	struct RuntimeClassCheck : Interface
	{
		static_assert(std::is_base_of<IUnknown, Interface>::value, "IUnknown check failed");
		static_assert(std::is_base_of<IInspectable, Interface>::value || std::is_base_of<IUnknown, Interface>::value, "IInspectable check failed");
	};
#pragma endregion

#pragma region Allocation strategy classes
	class DECLSPEC_NOVTABLE HeapAllocationStrategy : public IInspectable
	{
		static volatile ULONG m_objectCount;
		volatile ULONG m_references = 1;
	protected:
		HeapAllocationStrategy() throw()
		{
			InterlockedIncrement(&m_objectCount);
		}
		virtual ~HeapAllocationStrategy() throw()
		{
			InterlockedDecrement(&m_objectCount);
		}

		STDMETHODIMP_(ULONG) AddRefImpl() throw()
		{
			return InterlockedIncrement(&m_references);
		}
		STDMETHODIMP_(ULONG) ReleaseImpl() throw()
		{
			auto const remaining = InterlockedDecrement(&m_references);
			if (0 == remaining)
			{
				delete this;
			}
			return remaining;
		}
	public:
		static ULONG GetObjectCount() throw()
		{
			return m_objectCount;
		}
	};

#ifndef OBJECTCOUNT_H
#define OBJECTCOUNT_H
	volatile ULONG HeapAllocationStrategy::m_objectCount = 0;
#endif

	class DECLSPEC_NOVTABLE StackAllocationStrategy : public IInspectable
	{
		void* operator new(size_t) throw()
		{
			return nullptr;
		}
			void operator delete(void*) throw()
		{

		}
	protected:
		STDMETHODIMP_(ULONG) AddRefImpl() throw()
		{
			return 1;
		}
		STDMETHODIMP_(ULONG) ReleaseImpl() throw()
		{
			return 1;
		}
	};
#pragma endregion

#pragma region RuntimeClass template
	template <typename HeadInterface, typename ... TailInterfaces>
	class DECLSPEC_NOVTABLE RuntimeClassBase
		: public RuntimeClassCheck<HeadInterface>
		, public RuntimeClassCheck<TailInterfaces> ...
	{
		template <typename Head, typename ... Tail>
		void* QueryInterfaceImpl(GUID const& id) throw()
		{
			if (!IsCloaked<Head>::value && id == __uuidof(Head))
			{
				return static_cast<Head *>(this);
			}
			return QueryInterfaceImpl<Tail...>(id);
		}
		template <int = 0>
		void* QueryInterfaceImpl(GUID const&) throw()
		{
			return nullptr;
		}

		template <typename Head, typename ... Tail>
		void GetIidsImpl(GUID* ids) throw()
		{
			if (!IsCloaked<Head>::value)
			{
				*ids++ = __uuidof(Head);
			}
			GetIidsImpl<Tail ...>(ids);
		}
		template <int = 0>
		void GetIidsImpl(GUID*) throw()
		{
			return;
		}

		template <typename Head, typename ... Tail>
		SIZE_T CountInterfaces() throw()
		{
			return !IsCloaked<Head>::value + CountInterfaces<Tail...>();
		}
		template <int = 0>
		SIZE_T CountInterfaces() throw()
		{
			return 0;
		}
	protected:
		RuntimeClassBase() throw()
		{
		}
		virtual ~RuntimeClassBase() throw()
		{
		}

		STDMETHODIMP QueryInterfaceImpl(GUID const& id, void** object) throw()
		{
			if (id == __uuidof(HeadInterface) ||
				id == __uuidof(IUnknown) ||
				id == __uuidof(IInspectable))
			{
				*object = static_cast<HeadInterface *>(this);
			}
			else if (nullptr == (*object = QueryInterfaceImpl<TailInterfaces...>(id)))
			{
				return E_NOINTERFACE;
			}
			static_cast<IUnknown *>(*object)->AddRef();
			return S_OK;
		}
		STDMETHODIMP GetIidsImpl(ULONG* count, GUID** array) throw()
		{
			*count = CountInterfaces<HeadInterface, TailInterfaces...>();
			*array = static_cast<GUID *>(CoTaskMemAlloc(sizeof(GUID) * *count));
			if (nullptr == *array)
			{
				return E_OUTOFMEMORY;
			}
			GetIidsImpl<HeadInterface, TailInterfaces...>(*array);

			return S_OK;
		}
		STDMETHODIMP GetTrustLevelImpl(TrustLevel* trustLevel) throw()
		{
			*trustLevel = BaseTrust;
			return S_OK;
		}
	};

	template <typename HeadInterface, typename ... TailInterfaces>
	class DECLSPEC_NOVTABLE RuntimeClass
		: public HeapAllocationStrategy
		, public RuntimeClassBase < HeadInterface, TailInterfaces... >
	{
	protected:
		RuntimeClass() throw(){}
		virtual ~RuntimeClass() throw(){}
	public:
		STDMETHODIMP QueryInterface(GUID const& id, void** object) throw() override final
		{
			return QueryInterfaceImpl(id, object);
		}
		STDMETHODIMP GetIids(ULONG* count, GUID** array) throw() override final
		{
			return GetIidsImpl(count, array);
		}
		STDMETHODIMP GetTrustLevel(TrustLevel* trustLevel) throw() override final
		{
			return GetTrustLevelImpl(trustLevel);
		}
		STDMETHODIMP_(ULONG) AddRef() throw() override final
		{
			return AddRefImpl();
		}
		STDMETHODIMP_(ULONG) Release() throw() override final
		{
			return ReleaseImpl();
		}
	};
#pragma endregion

#pragma region ActivationFactory template
	template <typename RuntimeClassType, typename ... FactoryInterfaces >
	class DECLSPEC_NOVTABLE ActivationFactory
		: public StackAllocationStrategy
		, public RuntimeClassBase < IActivationFactory, IAgileObject, FactoryInterfaces...>
	{
	protected:
		template < typename RuntimeClassInterface, typename ... Args >
		STDMETHODIMP ActivateInstanceImpl(RuntimeClassInterface** result, Args&& ... args) throw()
		{
			if (nullptr == result)
			{
				return E_INVALIDARG;
			}
			*result = new(std::nothrow) RuntimeClassType(std::forward<Args>(args)...);
			return *result ? S_OK : E_OUTOFMEMORY;
		}
	public:
		STDMETHODIMP GetRuntimeClassName(HSTRING*) throw() override final
		{
			return E_ILLEGAL_METHOD_CALL;;
		}
		STDMETHODIMP QueryInterface(GUID const& id, void** object) throw() override final
		{
			return QueryInterfaceImpl(id, object);
		}
		STDMETHODIMP GetIids(ULONG* count, GUID** array) throw() override final
		{
			return GetIidsImpl(count, array);
		}
		STDMETHODIMP GetTrustLevel(TrustLevel* trustLevel) throw() override final
		{
			return GetTrustLevelImpl(trustLevel);
		}
		STDMETHODIMP_(ULONG) AddRef() throw() override final
		{
			return AddRefImpl();
		}
		STDMETHODIMP_(ULONG) Release() throw() override final
		{
			return ReleaseImpl();
		}
	};
#pragma endregion

#pragma region Module template
	template < typename ... Factories>
	class Module;

	template<>
	class DECLSPEC_NOVTABLE Module < >
	{
		template <typename HeadInterface, typename ... TailInterfaces>
		friend class RuntimeClassBase;

		volatile ULONG m_objectCount;

		void IncrementObjectCount() throw()
		{
			InterlockedIncrement(&m_objectCount);
		}
		void DecrementObjectCount() throw()
		{
			InterlockedDecrement(&m_objectCount);
		}
	protected:
		HRESULT GetActivationFactoryImpl(HSTRING, IActivationFactory**) throw()
		{
			return E_NOINTERFACE;
		}
	public:
		bool CanUnload() throw()
		{
			return m_objectCount == 0;
		}
	};

	template < typename HeadFactory, typename ... TailFactories >
	class DECLSPEC_NOVTABLE Module<HeadFactory, TailFactories...> : public Module < TailFactories... >
	{
		static_assert(std::is_base_of<StackAllocationStrategy, HeadFactory>::value, "Factory must derive from StackAllocationStrategy");
		HeadFactory m_factory;
	protected:
		Module() throw(){}

		HRESULT GetActivationFactoryImpl(HSTRING activatableClassId, IActivationFactory** factory) throw()
		{
			// Проверяем на равенство строки идентификатора класса и определенного нами класса
			if (0 == wcscmp(HeadFactory::GetRuntimeClassName(), WindowsGetStringRawBuffer(activatableClassId, nullptr)))
			{
				//Инициализируем указатель
				*factory = &m_factory;
				return S_OK;
			}
			return Module<TailFactories...>::GetActivationFactoryImpl(activatableClassId, factory);
		}
	public:
		static Module& GetModule() throw()
		{
			static Module singleton;
			return singleton;
		}

		HRESULT GetActivationFactory(HSTRING activatableClassId, IActivationFactory** factory) throw()
		{
			BOOL hasEmbedNull;
			//Проверяем идентфикатор класса и указатель на фабрику
			if (WindowsIsStringEmpty(activatableClassId) || FAILED(WindowsStringHasEmbeddedNull(activatableClassId, &hasEmbedNull)) || hasEmbedNull == TRUE || nullptr == factory)
			{
				//Если идентификатор не задан или указатель нулевой
				return E_INVALIDARG;
			}
			return GetActivationFactoryImpl(activatableClassId, factory);
		}
	};
#pragma endregion
}
