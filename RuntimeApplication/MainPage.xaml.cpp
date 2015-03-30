#include "pch.h"
#include "MainPage.xaml.h"

using namespace MTL;
using namespace MTL::Wrappers;
using namespace ABI::RuntimeApplication;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::Foundation;

class ABI::RuntimeApplication::MainPage sealed : public RuntimeClass<IMainPage, IPage, IUserControl, IControl, IFrameworkElement, IUIElement, IDependencyObject, IControlProtected>
{
	bool m_contentLoaded = false;
	ComPtr<IPage> m_basePage;
public:
	MainPage() noexcept
	{
		ComPtr<IPageFactory> pageFactory;
		VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Page).Get(), pageFactory.GetAddressOf()));

		VERIFY_SUCCEEDED(pageFactory->CreateInstance(static_cast<IMainPage *>(this), nullptr, m_basePage.GetAddressOf()));

		InitializeComponent();
	}

	STDMETHODIMP InitializeComponent() noexcept override final
	{
		if (m_contentLoaded)
			return S_OK;

		ComPtr<IApplicationStatics> appStatics;
		VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), appStatics.GetAddressOf()));

		ComPtr<IUriRuntimeClassFactory> uriFactory;
		VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), uriFactory.GetAddressOf()));

		ComPtr<IUriRuntimeClass> uri;
		VERIFY_SUCCEEDED(uriFactory->CreateUri(HStringReference(L"ms-appx:///MainPage.xaml").Get(), uri.GetAddressOf()));

		VERIFY_SUCCEEDED(appStatics->LoadComponentWithResourceLocation(static_cast<IMainPage *>(this), uri.Get(), ComponentResourceLocation::ComponentResourceLocation_Application));

		m_contentLoaded = true;
		return S_OK;
	}
};