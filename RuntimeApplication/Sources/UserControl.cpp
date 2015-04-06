#include "pch.h"
#include <WeakReference.h>
#include "UserControl.h"

using namespace MTL;
using namespace MTL::Wrappers;
using namespace RuntimeApplication;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml;

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

	ComPtr<IControl2> control;
	pInnerPointer->QueryInterface(control.GetAddressOf());

	auto cast = reinterpret_cast<RuntimeClassBase<IUserControl, IControl, IControlProtected, IControlOverrides, IControl2, IControl3, IControlExperimental, IContentControlOverrides> *>(pBasePointer);

	auto pCastControl = static_cast<IControl2 *>(cast);

	pCastControl->put_IsTextScaleFactorEnabled(false);

	boolean isEnabled = true;
	control->get_IsTextScaleFactorEnabled(&isEnabled);
	
	ASSERT(isEnabled == false);

	return S_OK;
}
