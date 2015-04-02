#pragma once
#include <MTL.h>
#include "MIDL\MainPage.xaml.h"

namespace ABI
{
	namespace RuntimeApplication
	{
		class MainPage sealed : public MTL::RuntimeClass<IMainPage, Windows::UI::Xaml::Markup::IComponentConnector>
		{
			MTL::ComPtr<IInspectable> m_inner;
			MTL::ComPtr<Windows::UI::Xaml::Controls::IPage> m_page;
		public:
			MainPage() noexcept;

			STDMETHODIMP QueryInterface(GUID const& id, void** object) noexcept override final
			{
				if (E_NOTIMPL == QueryInterface(id, object))
				{
					return m_inner->QueryInterface(id, object);
				}
				return S_OK;
			}
			STDMETHODIMP GetIids(ULONG* count, GUID** array) noexcept override final
			{
				ULONG innerCount;
				GUID* innerArray;

				m_inner->GetIids(&innerCount, &innerArray);

				CoTaskMemRealloc(static_cast<LPVOID>(innerArray), innerCount + BaseCountInterfaces());

				BaseGetIids(innerArray + innerCount);

				return S_OK;
			}
			STDMETHODIMP GetRuntimeClassName(HSTRING *result) noexcept override final
			{
				return WindowsCreateString(RuntimeClass_RuntimeApplication_MainPage, _countof(RuntimeClass_RuntimeApplication_MainPage), result);
			}
			STDMETHODIMP Connect(INT32, IInspectable *) noexcept override final
			{
				return S_OK;
			}
		};
	}
}