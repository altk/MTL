#pragma once
#include <Windows.h>
#include <inspectable.h>
#include <type_traits>

namespace mtl
{
	template <typename Interface>
	struct Cloaked : Interface {};

	template <typename Interface>
	struct IsCloaked : std::false_type {};

	template <typename Interface>
	struct IsCloaked<Cloaked<Interface>> : std::true_type{};

	template < typename ... Interfaces >
	class __declspec(novtable) RuntimeClass
		: public IInspectable
		, public Interfaces ...
	{
		template < typename ... Tail >
		void CopyInterfaces(GUID * ids) throw();
		template < typename End >
		void CopyInterfaces<End>(GUID * ids) throw()
		{
			if (!IsCloaked<End>)
			*ids = __uuidof(End);
		}
		template < typename Head, typename ... Tail >
		void CopyInterfaces<Head, Tail...>(GUID * ids) throw()
		{
			
		}

		template < typename ... Tail >
		constexpr unsigned CountInterfaces() throw();
		template < typename End >
		constexpr unsigned CountInterfaces<End>() throw()
		{
			return 1;
		}
		template < typename Head, typename ... Tail >
		constexpr unsigned CountInterfaces<Head, Tail...>() throw()
		{
			return !IsCloaked<Head>::value + CountInterfaces<Tail...>();
		}

		template < typename ... Tail >
		void * QueryInterfaceImpl(GUID const & id) throw();
		template < typename End >
		void * QueryInterfaceImpl<End>(GUID const & id) throw()
		{
			if (id == __uuidof(End) || id == __uuidof(IInspectable) || id == __uuidof(IUnknown))
			{
				return this;
			}
			return nullptr;
		}
		template < typename Head, typename ... Tail >
		void * QueryInterfaceImpl<Head, Tail...>(GUID const & id) throw()
		{
			if (id == __uuidof(Head) || id == __uuidof(IInspectable) || id == __uuidof(IUnknown))
			{
				return this;
			}
			return QueryInterfaceImpl<Tail>(id);
		}
	protected:
		ULONG m_references = 1;
		RuntimeClass() throw() = default;
		virtual ~RuntimeClass() throw()
		{}
	public:
		virtual STDMETHODIMP_(ULONG) AddRef() throw() override
		{
			return InterlockedIncrement(&m_references);
		}
		virtual STDMETHODIMP_(ULONG) Release() throw() override
		{
			auto const remaining = InterlockedDecrement(&m_references);
			if (0 == remaining)
			{
				delete this;
			}
			return remaining;
		}
		virtual STDMETHODIMP QueryInterface(GUID const & id, void ** object) throw() override
		{
			*object = QueryInterfaceImpl<Interfaces...>(id);
			if (nullptr == *object)
			{
				return E_NOINTERFACE;
			}
			static_cast<::IInspectable*>(*object)->AddRef();
			return S_OK;
		}
		virtual STDMETHODIMP GetIids(ULONG * count, GUID ** array) throw() override
		{
			*count = 0;
			*array = nullptr;
			unsigned const localCount = CountInterfaces<Interfaces ...>();
			if (0 == localCount)
			{
				return S_OK;
			}
			auto localArray = static_cast<GUID *>(CoTaskMemAlloc(sizeof(GUID) * localCount));
			if (nullptr == localArray)
			{
				return E_OUTOFMEMORY;
			}
		}
	};
}