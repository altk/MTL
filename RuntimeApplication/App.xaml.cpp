#include "pch.h"
#include <MTL.h>
#include <windows.ui.xaml.h>
#include <windows.ui.xaml.markup.h>
#include <windows.ui.xaml.interop.h>
#include <windows.ui.xaml.controls.h>
#include <windows.ui.xaml.controls.primitives.h>
#include <windows.foundation.h>
#include "MainPageActivationFactory.h"
#include "MainPage.xaml.h"

using namespace MTL;
using namespace MTL::Wrappers;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Interop;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::Foundation;
using namespace ABI::RuntimeApplication;

namespace RuntimeApplication
{
	class App sealed : public RuntimeClass<Inherited<IApplication>, IApplicationOverrides, IXamlMetadataProvider, IAgileObject>
	{
		using baseApplicationType = Inherited<IApplication>;

		ComPtr<IInspectable> m_inspectable;
		ComPtr<IApplicationOverrides> m_applicationOverrides;
	public:
		App() noexcept
		{
			ComPtr<IApplicationFactory> applicationFactory;
			VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), applicationFactory.GetAddressOf()));

			VERIFY_SUCCEEDED(applicationFactory->CreateInstance(static_cast<IApplicationOverrides *>(this), m_inspectable.GetAddressOf(), baseApplicationType::m_interface.GetAddressOf()));

			m_applicationOverrides = m_inspectable.As<IApplicationOverrides>();
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

			ComPtr<IMainPage> mainPage;
			VERIFY_SUCCEEDED(ActivateInstance(HStringReference(RuntimeClass_RuntimeApplication_MainPage).Get(), mainPage.GetAddressOf()));

			/*ComPtr<IUIElement> element;
			VERIFY_SUCCEEDED(window->get_Content(element.GetAddressOf()));*/

			return S_OK;
		}
	};

	class ApplicationInitializationCallback sealed : public RuntimeClassBase<StackAllocationStrategy, IApplicationInitializationCallback>
	{
	public:
		STDMETHODIMP Invoke(IApplicationInitializationCallbackParams *) noexcept override final
		{
			ComPtr<App> app{ new App() };
			return S_OK;
		}
	};
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	VERIFY_SUCCEEDED(RoInitialize(RO_INIT_TYPE::RO_INIT_MULTITHREADED));

	ComPtr<IApplicationStatics> applicationStatics;
	VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), applicationStatics.GetAddressOf()));

	RuntimeApplication::ApplicationInitializationCallback callback;
	applicationStatics->Start(&callback);
}

HRESULT WINAPI DllGetActivationFactory(HSTRING activatableClassId, IActivationFactory** factory) noexcept
{
	return Module<RuntimeApplication::MainPageActivationFactory>::GetModule().GetActivationFactory(activatableClassId, factory);
}

HRESULT WINAPI DllCanUnloadNow() noexcept
{
	return HeapAllocationStrategy::GetObjectCount() == 0 ? S_OK : S_FALSE;
}
