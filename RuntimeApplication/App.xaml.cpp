#include "pch.h"
#include <MTL.h>
#include <windows.ui.xaml.h>
#include <windows.ui.xaml.markup.h>
#include <windows.ui.xaml.interop.h>
#include <windows.ui.xaml.controls.h>
#include <windows.ui.xaml.controls.primitives.h>
#include <windows.foundation.h>

using namespace MTL;
using namespace MTL::Wrappers;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Interop;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::Foundation;

namespace RuntimeApplication
{
	class App sealed : public RuntimeClass<IXamlMetadataProvider>
	{
	public:
		App() noexcept
		{
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
	};

	class ApplicationInitializationCallback sealed : public RuntimeClass<IApplicationInitializationCallback>
	{
	public:
		STDMETHODIMP Invoke(IApplicationInitializationCallbackParams *) noexcept override final
		{
			App();
			return S_OK;
		}
	};
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	VERIFY_SUCCEEDED(RoInitialize(RO_INIT_TYPE::RO_INIT_MULTITHREADED));

	ComPtr<IApplicationStatics> applicationStatics;
	VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), applicationStatics.GetAddressOf()));

	ComPtr<RuntimeApplication::ApplicationInitializationCallback> applicationInitializationCallback(new RuntimeApplication::ApplicationInitializationCallback());
	applicationStatics->Start(applicationInitializationCallback.Get());
}
//
//int main(int, HSTRING *)
//{
//	ComPtr<IApplicationStatics> applicationStatics;
//	VERIFY_SUCCEEDED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), applicationStatics.GetAddressOf()));
//
//	applicationStatics->Start()
//
//	/*ComPtr
//
//	auto hr = Windows::Foundation::GetActivationFactory(Microsoft::WRL::Wrappers::HStringReference(RuntimeClass_Windows_UI_Xaml_Application).Get(), pAppStatics.GetAddressOf());
//	if (SUCCEEDED(hr)) {
//		Microsoft::WRL::ComPtr<App::AppInit> appInit = Microsoft::WRL::Make<App::AppInit>();
//		hr = pAppStatics->Start(appInit.Get());
//	}*/
//	return (FAILED(hr)) ? 0 : -1;
//}