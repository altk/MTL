#include "pch.h"
#include "DependencyObject.h"

using namespace MTL;
using namespace MTL::Wrappers;
using namespace RuntimeApplication;

STDMETHODIMP DependencyObject::ActivateInstance(DependencyObject ** result) noexcept
{
	*result = new (std::nothrow) DependencyObject();

	ComPtr<ABI::Windows::UI::Xaml::IDependencyObjectFactory> factory;
	Windows::Foundation::GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_DependencyObject).Get(), factory.GetAddressOf());

	ComPtr<ABI::Windows::UI::Xaml::IDependencyObject> dependencyObject;
	factory->CreateInstance(*result, (*result)->m_inspectable.GetAddressOf(), dependencyObject.GetAddressOf());

	return E_NOTIMPL;
}

STDMETHODIMP DependencyObject::GetRuntimeClassName(HSTRING * className)
{
	return E_NOTIMPL;
}

STDMETHODIMP DependencyObject::GetValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable ** returnValue)
{
	return GetBaseObject()->GetValue(dp, returnValue);
}

STDMETHODIMP DependencyObject::SetValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable * value)
{
	return GetBaseObject()->SetValue(dp, value);
}

STDMETHODIMP DependencyObject::ClearValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp)
{
	return E_NOTIMPL;
}

STDMETHODIMP DependencyObject::ReadLocalValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable ** returnValue)
{
	return E_NOTIMPL;
}

STDMETHODIMP DependencyObject::GetAnimationBaseValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable ** returnValue)
{
	return E_NOTIMPL;
}

STDMETHODIMP DependencyObject::get_Dispatcher(ABI::Windows::UI::Core::ICoreDispatcher ** value)
{
	return E_NOTIMPL;
}
