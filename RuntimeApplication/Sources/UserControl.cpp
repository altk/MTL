#include "pch.h"
#include <WeakReference.h>
#include "UserControl.h"
#include <typeinfo>

using namespace MTL;
using namespace MTL::Wrappers;
using namespace RuntimeApplication;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml;


template<typename ... Interfaces>
struct Tester;

template<typename Head, typename ... Tail>
struct Tester<Head, Tail...>
{
	static void Test(IInspectable* source, RuntimeClassBase<Head, Tail...> * cast)
	{
		ComPtr<Head> query;
		VERIFY_SUCCEEDED(source->QueryInterface(query.GetAddressOf()));

		OutputDebugStringA("\r\n");
		OutputDebugStringA(typeid(Head).name());

		ASSERT((int)query.Get() == (int)static_cast<Head *>(cast));

		auto innerCast = reinterpret_cast<RuntimeClassBase<Tail...> *>(reinterpret_cast<IInspectable *>(cast) + 1);

		Tester<Tail...>::Test(source, innerCast);
	}
};

template<typename End>
struct Tester<End>
{
	static void Test(IInspectable *source, RuntimeClassBase<End> *cast)
	{
		ComPtr<End> query;
		VERIFY_SUCCEEDED(source->QueryInterface(query.GetAddressOf()));

		ASSERT((int)query.Get() == (int)static_cast<End *>(cast));
	}
};

template<typename ... Interfaces>
void TestInterfaces(IInspectable *source, RuntimeClassBase<Interfaces...> *cast)
{
	Tester<Interfaces...>::Test(source, cast);
}

HRESULT RuntimeApplication::UserControl::ActivateInstance(UserControl ** result) noexcept
{
	*result = new (std::nothrow) RuntimeApplication::UserControl();

	ComPtr<IUserControlFactory> factory;
	Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_UserControl).Get(), factory.GetAddressOf());

	factory->CreateInstance(
		static_cast<IUserControl *>(*result),
		(*result)->m_inner.GetAddressOf(),
		reinterpret_cast<IUserControl **>((*result)->m_base.GetAddressOf()));

	auto pInnerPointer = (*result)->m_inner.Get();
	auto pBasePointer = (*result)->m_base.Get();

	ASSERT((int)*((IInspectable**)pInnerPointer + 1) == (int)*result);
	ASSERT((int)(pInnerPointer + 2) == (int)pBasePointer);

	auto cast = reinterpret_cast<RuntimeClassBase<IUserControl,
		IControl,
		IControlProtected,
		IControlOverrides,		
		IControl2,
		IControl3,
		IControlExperimental,
		IControlOverridesExperimental,
		IFrameworkElement,
		IFrameworkElementOverrides,
		IFrameworkElement2,
		IFrameworkElementOverrides2,
		IFrameworkElementExperimental,
		IUIElement,
		IUIElementOverrides,
		IUIElement2,
		IUIElement3,
		IUIElementExperimental,
		IDependencyObject,
		IDependencyObject2> *>(pBasePointer);

	TestInterfaces(pInnerPointer, cast);

	//IControlOverridesExperimental test
	{
		ComPtr<IControlOverridesExperimental> query;
		pInnerPointer->QueryInterface(query.GetAddressOf());

		ASSERT((int)query.Get() == (int)static_cast<IControlOverridesExperimental *>(cast));
	}

	//IUIElementExperimental test
	{
		ComPtr<IUIElementExperimental> query;
		pInnerPointer->QueryInterface(query.GetAddressOf());

		ASSERT((int)query.Get() == (int)static_cast<IUIElementExperimental *>(cast));
	}

	{
		ComPtr<IControl2> control;
		pInnerPointer->QueryInterface(control.GetAddressOf());

		auto pCastControl = static_cast<IControl2 *>(cast);

		pCastControl->put_IsTextScaleFactorEnabled(false);

		boolean isEnabled = true;
		control->get_IsTextScaleFactorEnabled(&isEnabled);

		ASSERT(isEnabled == false);
	}

	return S_OK;
}
