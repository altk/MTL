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

#pragma region Statick ckecks
	template <typename Interface>
	struct RuntimeClassCheck : Interface
	{
		static_assert(std::is_base_of<IUnknown, Interface>::value, "IUnknown check failed");
		static_assert(std::is_base_of<IInspectable, Interface>::value || std::is_base_of<IUnknown, Interface>::value, "IInspectable check failed");
	};
#pragma endregion

#pragma region RuntimeClass template

	template <typename HeadInterface, typename ... TailInterfaces>
	class DECLSPEC_NOVTABLE RuntimeClass
		: public RuntimeClassCheck<HeadInterface>
		, public RuntimeClassCheck<TailInterfaces> ...
	{
		volatile ULONG m_references = 1;

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
		RuntimeClass() throw()
		{
		}

		virtual ~RuntimeClass() throw()
		{
		}

	public:
		STDMETHODIMP QueryInterface(GUID const& id, void** object) throw() override final
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

		STDMETHODIMP GetIids(ULONG* count, GUID** array) throw() override final
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

		STDMETHODIMP_(ULONG) AddRef() throw() override final
		{
			return InterlockedIncrement(&m_references);
		}

		STDMETHODIMP_(ULONG) Release() throw() override final
		{
			auto const remaining = InterlockedDecrement(&m_references);
			if (0 == remaining)
			{
				delete this;
			}
			return remaining;
		}

		STDMETHODIMP GetTrustLevel(TrustLevel* trustLevel) throw() override final
		{
			*trustLevel = BaseTrust;
			return S_OK;
		}
	};
#pragma endregion

#pragma region ActivationFactory template
	template <typename FactoryInterface, typename RuntimeClassType >
	class DECLSPEC_NOVTABLE ActivationFactory : public RuntimeClass < FactoryInterface, IActivationFactory, IAgileObject >
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

		template < typename ... Args >
		STDMETHODIMP ActivateInstanceImpl(IInspectable** result, Args&& ... args) throw()
		{
			if (nullptr == result)
			{
				return E_INVALIDARG;
			}
			*result = reinterpret_cast<IInspectable*>(new(std::nothrow) RuntimeClassType(std::forward<Args>(args)...));
			return *result ? S_OK : E_OUTOFMEMORY;
		}
	public:
		STDMETHODIMP GetRuntimeClassName(HSTRING*) throw() override final
		{
			return E_ILLEGAL_METHOD_CALL;;
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
		friend class RuntimeClass;

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
		HeadFactory m_factory;
	protected:
		Module() throw(){}

		HRESULT GetActivationFactoryImpl(HSTRING activatableClassId, IActivationFactory** factory) throw()
		{
			// ��������� �� ��������� ������ �������������� ������ � ������������� ���� ������
			if (0 == wcscmp(HeadFactory::GetRuntimeClassName(), WindowsGetStringRawBuffer(activatableClassId, nullptr)))
			{
				//�������������� ���������
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
			//��������� ������������ ������ � ��������� �� �������
			if (WindowsIsStringEmpty(activatableClassId) || FAILED(WindowsStringHasEmbeddedNull(activatableClassId, &hasEmbedNull)) || hasEmbedNull == TRUE || nullptr == factory)
			{
				//���� ������������� �� ����� ��� ��������� �������
				return E_INVALIDARG;
			}
			return GetActivationFactoryImpl(activatableClassId, factory);
		}
	};
#pragma endregion
}
