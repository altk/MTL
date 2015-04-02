#include "pch.h"
#include "MainPage.h"

using namespace MTL::Wrappers;
using namespace MTL;
using namespace ABI::RuntimeApplication;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::Foundation;

MainPage::MainPage() noexcept
{
	ComPtr<IPageFactory> pageFactory;
	VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Page).Get(), pageFactory.GetAddressOf()));

	VERIFY_SUCCEEDED(pageFactory->CreateInstance(static_cast<IMainPage *>(this), m_inner.GetAddressOf(), m_page.GetAddressOf()));

	m_controlOverrides = m_inner.As<IControlOverrides>();
	m_pageOverrides = m_inner.As<IPageOverrides>();
	m_frameworkElementOverrides = m_inner.As<IFrameworkElementOverrides>();
	m_uiElementOverrides = m_inner.As<IUIElementOverrides>();
	
	ComPtr<IApplicationStatics> appStatics;
	VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), appStatics.GetAddressOf()));

	ComPtr<IUriRuntimeClassFactory> uriFactory;
	VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), uriFactory.GetAddressOf()));

	ComPtr<IUriRuntimeClass> uri;
	VERIFY_SUCCEEDED(uriFactory->CreateUri(HStringReference(L"ms-appx:///XAML/MainPage.xaml").Get(), uri.GetAddressOf()));

	auto hr = appStatics->LoadComponentWithResourceLocation(static_cast<IMainPage *>(this), uri.Get(), ComponentResourceLocation::ComponentResourceLocation_Application);
	//VERIFY_SUCCEEDED(hr);
}