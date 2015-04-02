#include "pch.h"
#include <windows.ui.xaml.h>
#include <windows.ui.xaml.markup.h>
#include <windows.ui.xaml.interop.h>
#include "MainPage.h"

using namespace MTL::Wrappers;
using namespace MTL;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Interop;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::Foundation;
using namespace ABI::RuntimeApplication;

namespace RuntimeApplication
{
	class App sealed : public RuntimeClass<IApplicationOverrides, IXamlMetadataProvider, IAgileObject>
	{
		ComPtr<IApplication> m_application;
		ComPtr<IApplicationOverrides> m_applicationOverrides;
	public:
		App() noexcept
		{
			ComPtr<IApplicationFactory> applicationFactory;
			VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), applicationFactory.GetAddressOf()));

			ComPtr<IInspectable> inspectable;
			VERIFY_SUCCEEDED(applicationFactory->CreateInstance(static_cast<IApplicationOverrides *>(this), inspectable.GetAddressOf(), m_application.GetAddressOf()));

			m_applicationOverrides = inspectable.As<IApplicationOverrides>();
		}

		STDMETHODIMP GetRuntimeClassName(HSTRING*) noexcept override final
		{
			return E_ILLEGAL_METHOD_CALL;
		}

		STDMETHODIMP GetXamlType(TypeName type, IXamlType ** xamlType) noexcept override final
		{
			return S_OK;
		}
		STDMETHODIMP GetXamlTypeByFullName(HSTRING string, IXamlType ** xamlType) noexcept override final
		{
			return S_OK;
		}
		STDMETHODIMP GetXmlnsDefinitions(UINT32 *, XmlnsDefinition ** xmlnsDefinition) noexcept override final
		{
			return S_OK;
		}

		STDMETHODIMP OnActivated(IActivatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnActivated(args);
		}
		STDMETHODIMP OnFileActivated(IFileActivatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnFileActivated(args);
		}
		STDMETHODIMP OnSearchActivated(ISearchActivatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnSearchActivated(args);
		}
		STDMETHODIMP OnShareTargetActivated(IShareTargetActivatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnShareTargetActivated(args);
		}
		STDMETHODIMP OnFileOpenPickerActivated(IFileOpenPickerActivatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnFileOpenPickerActivated(args);
		}
		STDMETHODIMP OnFileSavePickerActivated(IFileSavePickerActivatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnFileSavePickerActivated(args);
		}
		STDMETHODIMP OnCachedFileUpdaterActivated(ICachedFileUpdaterActivatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnCachedFileUpdaterActivated(args);
		}
		STDMETHODIMP OnWindowCreated(IWindowCreatedEventArgs *args) noexcept override final
		{
			return m_applicationOverrides->OnWindowCreated(args);
		}
		STDMETHODIMP OnLaunched(ILaunchActivatedEventArgs *args) noexcept override final
		{
			ComPtr<IWindowStatics> windowStatics;
			VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Window).Get(), windowStatics.GetAddressOf()));

			ComPtr<IWindow> window;
			VERIFY_SUCCEEDED(windowStatics->get_Current(window.GetAddressOf()));

			ComPtr<IMainPage> mainPage(static_cast<IMainPage *>(new (std::nothrow) MainPage()));

			VERIFY_SUCCEEDED(window->put_Content(mainPage.As<IUIElement>().Get()));

			VERIFY_SUCCEEDED(window->Activate());

			return S_OK;
		}
	};

	class ApplicationInitializationCallback sealed : public StackAllocationStrategy<IApplicationInitializationCallback>
	{
	public:
		STDMETHODIMP Invoke(IApplicationInitializationCallbackParams *) noexcept override final
		{
			//App();
			return S_OK;
		}
	};
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	VERIFY_SUCCEEDED(RoInitialize(RO_INIT_TYPE::RO_INIT_MULTITHREADED));

	ComPtr<IApplicationStatics> applicationStatics;
	VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), applicationStatics.GetAddressOf()));

	auto hs = sizeof(IApplicationInitializationCallback);

	auto a = sizeof(RuntimeApplication::ApplicationInitializationCallback);

	static_assert(sizeof(IApplicationInitializationCallback) == sizeof(RuntimeApplication::ApplicationInitializationCallback), "ASSERT");

	RuntimeApplication::ApplicationInitializationCallback callback;
	applicationStatics->Start(&callback);
}