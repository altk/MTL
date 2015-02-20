#pragma once
#include <Windows.h>
#include <inspectable.h>
#include <type_traits>

namespace mtl
{
	template < typename Interface >
	struct Cloaked : Interface {};

	template < typename Interface >
	struct IsCloaked : std::false_type {};

	template < typename Interface >
	struct IsCloaked<Cloaked<Interface>> : std::true_type{};

	template < typename Interface >
	struct IInspectableTraits : Interface
	{
		IInspectableTraits()
		{
			if (std::is_base_of<IInspectable, Interface>::value)
				return;
			static_assert(L"Runtime class template can derived only Inspectable classes.");
		}
	};

	template < typename Head, typename ... Tail>
	class RuntimeClass
		: public IInspectableTraits< Head >
		, public RuntimeClass < Tail... >
	{
	protected:
		void * QueryInterfaceImpl(GUID const & id) throw()
		{
			if (__uuidof(Head) == id)
			{
				return this;
			}
			return RuntimeClass<Tail...>::QueryInterfaceImpl(id);
		}
		void GetIidsImpl(GUID * ids) throw()
		{
			*ids++ = __uuidof(Head);
			if (sizeof...(Tail) == 0)
			{
				return;
			}
			RuntimeClass<Tail...>::GetIidsImpl(ids);
		}
	public:
		virtual STDMETHODIMP QueryInterface(GUID const & id, void ** object) throw() override
		{
			*object == nullptr;
			*object = QueryInterfaceImpl(id);
			if (nullptr == *object)
			{
				return E_NOINTERFACE;
			}
			static_cast<IInspectable*>(*object)->AddRef();
			return S_OK;
		}
		virtual STDMETHODIMP GetIids(ULONG * count, GUID ** array) throw() override
		{
			*count = 2 + sizeof...(Tail);
			*array = static_cast<GUID *>(CoTaskMemAlloc(sizeof(GUID) * *count));
			if (nullptr == *array)
			{
				return E_OUTOFMEMORY;
			}
			GetIidsImpl(*array);
			return S_OK;
		}
	};

	template < typename End >
	class RuntimeClass<End>
		: public IInspectable
	{
	protected:
		ULONG m_references = 1;
		RuntimeClass() throw(){}
		virtual ~RuntimeClass() throw()
		{}
		void * QueryInterfaceImpl(GUID const & id) throw()
		{
			if (__uuidof(IInspectable) == id)
			{
				return this;
			}
			return nullptr;
		}
		void GetIidsImpl(GUID * ids) throw()
		{
			*ids = __uuidof(IInspectable);
		}
	public:
		virtual STDMETHODIMP_(ULONG) AddRef() throw() override final
		{
			return InterlockedIncrement(&m_references);
		}
		virtual STDMETHODIMP_(ULONG) Release() throw() override  final
		{
			auto const remaining = InterlockedDecrement(&m_references);
			if (0 == remaining)
			{
				delete this;
			}
			return remaining;
		}
		virtual STDMETHODIMP GetTrustLevel(TrustLevel * trustLevel) throw() override final
		{
			*trustLevel = BaseTrust;
			return S_OK;
		}
	};
}