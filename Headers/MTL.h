#pragma once
#include <roapi.h>
#include <Windows.h>
#include <winstring.h>
#include <inspectable.h>
#include <type_traits>
#include <activation.h>
#include <new>
#include <string.h>
#include <ObjIdlbase.h>
#include <utility>
#include "ASSERT.h"
#include "VERIFY.h"
#include "TRACE.h"

namespace MTL
{
#pragma region Exception
	struct Exception
	{
		HRESULT Result;

		explicit Exception(HRESULT const result) noexcept
			: Result(result)
		{
		}
	};

	void Check(HRESULT const result)
	{
		if (S_OK != result)
		{
			throw Exception(result);
		}
	}
#pragma endregion

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
		HeapAllocationStrategy() noexcept
		{
			InterlockedIncrement(&m_objectCount);
		}
		virtual ~HeapAllocationStrategy() noexcept
		{
			InterlockedDecrement(&m_objectCount);
		}

		STDMETHODIMP_(ULONG) AddRefImpl() noexcept
		{
			return InterlockedIncrement(&m_references);
		}
		STDMETHODIMP_(ULONG) ReleaseImpl() noexcept
		{
			auto const remaining = InterlockedDecrement(&m_references);
			if (0 == remaining)
			{
				delete this;
			}
			return remaining;
		}
	public:
		static ULONG GetObjectCount() noexcept
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
	protected:
		STDMETHODIMP_(ULONG) AddRefImpl() noexcept
		{
			return 1;
		}
		STDMETHODIMP_(ULONG) ReleaseImpl() noexcept
		{
			return 1;
		}
		void * operator new(std::size_t) = delete;
		void * operator new[](std::size_t) = delete;
		void operator delete(void *) = delete;
		void operator delete[](void *) = delete;
	};
#pragma endregion

#pragma region RuntimeClass template
	template <typename HeadInterface, typename ... TailInterfaces>
	class DECLSPEC_NOVTABLE RuntimeClassBase
		: public RuntimeClassCheck<HeadInterface>
		, public RuntimeClassCheck<TailInterfaces> ...
	{
		template <typename Head, typename ... Tail>
		void* QueryInterfaceImpl(GUID const& id) noexcept
		{
			if (!IsCloaked<Head>::value && id == __uuidof(Head))
			{
				return static_cast<Head *>(this);
			}
			return QueryInterfaceImpl<Tail...>(id);
		}
		template <int = 0>
		void* QueryInterfaceImpl(GUID const&) noexcept
		{
			return nullptr;
		}

		template <typename Head, typename ... Tail>
		void GetIidsImpl(GUID* ids) noexcept
		{
			if (!IsCloaked<Head>::value)
			{
				*ids++ = __uuidof(Head);
			}
			GetIidsImpl<Tail ...>(ids);
		}
		template <int = 0>
		void GetIidsImpl(GUID*) noexcept
		{
			return;
		}

		template <typename Head, typename ... Tail>
		SIZE_T CountInterfaces() noexcept
		{
			return !IsCloaked<Head>::value + CountInterfaces<Tail...>();
		}
		template <int = 0>
		SIZE_T CountInterfaces() noexcept
		{
			return 0;
		}
	protected:
		RuntimeClassBase() noexcept
		{
		}
		virtual ~RuntimeClassBase() noexcept
		{
		}

		STDMETHODIMP QueryInterfaceImpl(GUID const& id, void** object) noexcept
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
		STDMETHODIMP GetIidsImpl(ULONG* count, GUID** array) noexcept
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
		STDMETHODIMP GetTrustLevelImpl(TrustLevel* trustLevel) noexcept
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
		RuntimeClass() noexcept {}
		virtual ~RuntimeClass() noexcept {}
	public:
		STDMETHODIMP QueryInterface(GUID const& id, void** object) noexcept override final
		{
			return QueryInterfaceImpl(id, object);
		}
		STDMETHODIMP GetIids(ULONG* count, GUID** array) noexcept override final
		{
			return GetIidsImpl(count, array);
		}
		STDMETHODIMP GetTrustLevel(TrustLevel* trustLevel) noexcept override final
		{
			return GetTrustLevelImpl(trustLevel);
		}
		STDMETHODIMP_(ULONG) AddRef() noexcept override final
		{
			return AddRefImpl();
		}
		STDMETHODIMP_(ULONG) Release() noexcept override final
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
		STDMETHODIMP ActivateInstanceImpl(RuntimeClassInterface** result, Args&& ... args) noexcept
		{
			if (nullptr == result)
			{
				return E_INVALIDARG;
			}
			*result = new(std::nothrow) RuntimeClassType(std::forward<Args>(args)...);
			return *result ? S_OK : E_OUTOFMEMORY;
		}
	public:
		STDMETHODIMP GetRuntimeClassName(HSTRING*) noexcept override final
		{
			return E_ILLEGAL_METHOD_CALL;;
		}
		STDMETHODIMP QueryInterface(GUID const& id, void** object) noexcept override final
		{
			return QueryInterfaceImpl(id, object);
		}
		STDMETHODIMP GetIids(ULONG* count, GUID** array) noexcept override final
		{
			return GetIidsImpl(count, array);
		}
		STDMETHODIMP GetTrustLevel(TrustLevel* trustLevel) noexcept override final
		{
			return GetTrustLevelImpl(trustLevel);
		}
		STDMETHODIMP_(ULONG) AddRef() noexcept override final
		{
			return AddRefImpl();
		}
		STDMETHODIMP_(ULONG) Release() noexcept override final
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

		void IncrementObjectCount() noexcept
		{
			InterlockedIncrement(&m_objectCount);
		}
		void DecrementObjectCount() noexcept
		{
			InterlockedDecrement(&m_objectCount);
		}
	protected:
		HRESULT GetActivationFactoryImpl(HSTRING, IActivationFactory**) noexcept
		{
			return E_NOINTERFACE;
		}
	public:
		bool CanUnload() noexcept
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
		Module() noexcept {}

		HRESULT GetActivationFactoryImpl(HSTRING activatableClassId, IActivationFactory** factory) noexcept
		{
			if (0 == wcscmp(HeadFactory::GetRuntimeClassName(), WindowsGetStringRawBuffer(activatableClassId, nullptr)))
			{
				*factory = &m_factory;
				return S_OK;
			}
			return Module<TailFactories...>::GetActivationFactoryImpl(activatableClassId, factory);
		}
	public:
		static Module& GetModule() noexcept
		{
			static Module singleton;
			return singleton;
		}

		HRESULT GetActivationFactory(HSTRING activatableClassId, IActivationFactory** factory) noexcept
		{
			BOOL hasEmbedNull;
			if (WindowsIsStringEmpty(activatableClassId) || FAILED(WindowsStringHasEmbeddedNull(activatableClassId, &hasEmbedNull)) || hasEmbedNull == TRUE || nullptr == factory)
			{
				return E_INVALIDARG;
			}
			return GetActivationFactoryImpl(activatableClassId, factory);
		}
	};
#pragma endregion

#pragma region RemoveAddRefRelease
	template <typename Interface>
	class RemoveAddRefRelease : public Interface
	{
		STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();
	};
#pragma endregion

#pragma region ComPtr
	template <typename Interface>
	class ComPtr
	{
		template <typename T>
		friend class ComPtr;

		Interface * m_ptr = nullptr;

		void InternalAddRef() const noexcept
		{
			if (m_ptr)
			{
				m_ptr->AddRef();
			}
		}
		void InternalRelease() noexcept
		{
			Interface * temp = m_ptr;
			if (temp)
			{
				m_ptr = nullptr;
				temp->Release();
			}
		}
		void InternalCopy(Interface * other) noexcept
		{
			if (m_ptr != other)
			{
				InternalRelease();
				m_ptr = other;
				InternalAddRef();
			}
		}
		template <typename T>
		void InternalMove(ComPtr<T> & other) noexcept
		{
			if (m_ptr != other.m_ptr)
			{
				InternalRelease();
				m_ptr = other.m_ptr;
				other.m_ptr = nullptr;
			}
		}
	public:
		ComPtr() noexcept = default;
		ComPtr(ComPtr const & other) noexcept
			: m_ptr(other.m_ptr)
		{
			InternalAddRef();
		}
		template <typename T>
		ComPtr(ComPtr<T> const & other) noexcept
			: m_ptr(other.m_ptr)
		{
			InternalAddRef();
		}
		template <typename T>
		ComPtr(ComPtr<T> && other) noexcept
			: m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}

		~ComPtr() noexcept
		{
			InternalRelease();
		}

		ComPtr & operator=(ComPtr const & other) noexcept
		{
			InternalCopy(other.m_ptr);
			return *this;
		}
		template <typename T>
		ComPtr & operator=(ComPtr<T> const & other) noexcept
		{
			InternalCopy(other.m_ptr);
			return *this;
		}
		template <typename T>
		ComPtr & operator=(ComPtr<T> && other) noexcept
		{
			InternalMove(other);
			return *this;
		}
		explicit operator bool() const noexcept
		{
			return nullptr != m_ptr;
		}

		void Swap(ComPtr & other) noexcept
		{
			Interface * temp = m_ptr;
			m_ptr = other.m_ptr;
			other.m_ptr = temp;
		}

		Interface * Get() const noexcept
		{
			return m_ptr;
		}
		void Attach(Interface * other) noexcept
		{
			InternalRelease();
			m_ptr = other;
		}
		Interface * Detach() noexcept
		{
			Interface * temp = m_ptr;
			m_ptr = nullptr;
			return temp;
		}
		void Reset() noexcept
		{
			InternalRelease();
		}
		Interface ** GetAddressOf() noexcept
		{
			ASSERT(m_ptr == nullptr);
			return &m_ptr;
		}
		void CopyTo(Interface ** other) const noexcept
		{
			InternalAddRef();
			*other = m_ptr;
		}
		template <typename T>
		ComPtr<T> As() const noexcept
		{
			ComPtr<T> temp;
			m_ptr->QueryInterface(temp.GetAddressOf());
			return temp;
		}

		RemoveAddRefRelease<Interface> * operator->() const noexcept
		{
			return static_cast<RemoveAddRefRelease<Interface> *>(m_ptr);
		}
	};

	template <typename Interface>
	void swap(ComPtr<Interface> & left, ComPtr<Interface> & right) noexcept
	{
		left.Swap(right);
	}
#pragma endregion

	template <typename T>
	HRESULT GetActivationFactory(HSTRING activatableClassId, ComPtr<T> & factory) noexcept
	{
		return RoGetActivationFactory(activatableClassId, __uuidof(T), reinterpret_cast<void**>(factory.GetAddressOf()));
	}
}

namespace MTL
{
	namespace Wrappers
	{
#pragma region Handle
		template <typename Traits>
		class Handle
		{
			using Pointer = typename Traits::Pointer;

			Pointer m_value;

			void Close() noexcept
			{
				if (*this)
				{
					Traits::Close(m_value);
				}
			}
		public:
			Handle(Handle const &) = default;
			Handle & operator=(Handle const &) = default;
			explicit Handle(Pointer value = Traits::Invalid()) noexcept
				: m_value(value)
			{
			}
			Handle(Handle && other) noexcept
				: m_value(other.Detach())
			{
			}

			Handle & operator=(Handle && other) noexcept
			{
				if (this != other)
				{
					Attach(other.Detach());
				}

				return *this;
			}

			~Handle() noexcept
			{
				Close();
			}

			explicit operator bool() const noexcept
			{
				return m_value != Traits::Invalid();
			}

			Pointer Get() const noexcept
			{
				return m_value;
			}
			Pointer * GetAddressOf() noexcept
			{
				ASSERT(!*this);
				return &m_value;
			}

			bool Attach(Pointer value = Traits::Invalid()) noexcept
			{
				if (m_value != value)
				{
					Close();
					m_value = value;
				}
				return static_cast<bool>(*this);
			}
			Pointer Detach() noexcept
			{
				Pointer value = m_value;
				m_value = Traits::Invalid();
				return value;
			}

			void Swap(Handle & other) noexcept
			{
				std::swap(m_value, other.m_value);
			}
		};

		template<typename Traits>
		void swap(Handle<Traits> & left, Handle<Traits> & right) noexcept
		{
			left.Swap(right);
		}
#pragma endregion

#pragma region HStringTraits
		struct HStringTraits
		{
			using Pointer = HSTRING;

			static Pointer Invalid() noexcept
			{
				return nullptr;
			}

			static void Close(Pointer value) noexcept
			{
				VERIFY(S_OK == WindowsDeleteString(value));
			}
		};
#pragma endregion

#pragma region HString
		using HString = Handle<HStringTraits>;

		HString CreateString(wchar_t const * const string, unsigned const length)
		{
			HString result;
			Check(WindowsCreateString(string, length, result.GetAddressOf()));
			return result;
		}

		template <unsigned Count>
		HString CreateString(wchar_t const (&string)[Count])
		{
			return CreateString(string, Count - 1);
		}

		wchar_t const * Buffer(HString const & string) noexcept
		{
			return WindowsGetStringRawBuffer(string.Get(), nullptr);
		}

		wchar_t const * Buffer(HString const & string, unsigned & length) noexcept
		{
			return WindowsGetStringRawBuffer(string.Get(), &length);
		}

		unsigned Length(HString const & string) noexcept
		{
			return WindowsGetStringLen(string.Get());
		}

		bool Empty(HString const & string) noexcept
		{
			return 0 != WindowsIsStringEmpty(string.Get());
		}

		HString Duplicate(HString const & string)
		{
			HString result;

			Check(WindowsDuplicateString(string.Get(), result.GetAddressOf()));

			return result;
		}

		HString Substring(HString const & string, unsigned const start)
		{
			HString result;

			Check(WindowsSubstring(string.Get(), start, result.GetAddressOf()));

			return result;
		}
#pragma endregion

#pragma region HStringReference
		class HStringReference
		{
			HSTRING m_string;
			HSTRING_HEADER m_header;

		public:
			HStringReference(HStringReference const &) = delete;
			HStringReference & operator=(HStringReference const &) = delete;
			void * operator new(std::size_t) = delete;
			void * operator new[](std::size_t) = delete;
			void operator delete(void *) = delete;
			void operator delete[](void *) = delete;

			HStringReference(wchar_t const * const value, unsigned length)
			{
				Check(WindowsCreateStringReference(value, length, &m_header, &m_string));
			}
			template <unsigned Count>
			HStringReference(wchar_t const (&value)[Count])
				: HStringReference(value, Count-1)
			{
			}

			HSTRING Get() const noexcept 
			{
				return m_string;
			}
		};
#pragma endregion

	}
}
