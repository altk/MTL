#pragma once
#include <Windows.h>
#include <inspectable.h>
#include <unordered_set>
#include <type_traits>
#include <cstdint>

static_assert(sizeof(_GUID) == 128 / CHAR_BIT, "GUID");

namespace std
{
	template<>
	struct hash<GUID>
	{
		size_t operator()(const GUID& guid) const throw()
		{
			auto p = reinterpret_cast<const uint64_t*>(&guid);
			hash<uint64_t> hash;
			return hash(p[0]) ^ hash(p[1]);
		}
	};
}

namespace MTL
{
	template < typename Interface >
	struct Cloaked : Interface {};

	template < typename Interface >
	struct IsCloaked : std::false_type {};

	template < typename Interface >
	struct IsCloaked<Cloaked<Interface>> : std::true_type{};

	template < typename Interface >
	struct IInspectableCheck : Interface
	{
		static_assert(std::is_base_of<IInspectable, Interface>::value, "You must specify only IInspectable interfaces");
	};

	template <typename ... Interfaces >
	class DECLSPEC_NOVTABLE RuntimeClass : public Interfaces ... 
	{
		ULONG m_references = 1;
		static std::unordered_set<GUID> const m_iids;

		template<typename Head, typename ... Tail>
		void GetIidsImpl(GUID * ids) throw()
		{
			*ids++ = __uuidof(Head);
			GetIidsImpl<Tail...>(ids);
		}
		template<int = 0>
		void GetIidsImpl(GUID *) throw()
		{
			return;
		}
	protected:
		RuntimeClass() throw() {}
		virtual ~RuntimeClass() throw() {}
	public:
		STDMETHODIMP QueryInterface(GUID const & id, void ** object) throw() override final
		{
			if (m_iids.find(id) != m_iids.end())
			{
				*object = this;
				static_cast<IInspectable*>(*object)->AddRef();
				return S_OK;
			}
			return E_NOINTERFACE;
		}
		STDMETHODIMP GetIids(ULONG * count, GUID ** array) throw() override final
		{
			*count = sizeof...(Interfaces);
			*array = static_cast<GUID *>(CoTaskMemAlloc(sizeof(GUID) * *count));
			if (nullptr == *array)
			{
				return E_OUTOFMEMORY;
			}
			GetIidsImpl<Interfaces...>(*array);
			return S_OK;
		}
		STDMETHODIMP_(ULONG) AddRef() throw() override final
		{
			return InterlockedIncrement(&m_references);
		}
		STDMETHODIMP_(ULONG) Release() throw() override  final
		{
			auto const remaining = InterlockedDecrement(&m_references);
			if (0 == remaining)
			{
				delete this;
			}
			return remaining;
		}
		STDMETHODIMP GetTrustLevel(TrustLevel * trustLevel) throw() override final
		{
			*trustLevel = BaseTrust;
			return S_OK;
		}
	};

	template <typename ... Interfaces>
	std::unordered_set<GUID> const RuntimeClass<Interfaces...>::m_iids = std::unordered_set<GUID>{ _uuidof(IUnknown), __uuidof(IInspectable), __uuidof(Interfaces)... };
}