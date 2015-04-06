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
	factory->CreateInstance(*result, (*result)->m_inner.GetAddressOf(), reinterpret_cast<ABI::Windows::UI::Xaml::IDependencyObject **>((*result)->m_base.GetAddressOf()));
	
	return S_OK;
}

STDMETHODIMP DependencyObject::GetRuntimeClassName(HSTRING * className)
{
	return E_NOTIMPL;
}

STDMETHODIMP DependencyObject::GetValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable ** returnValue)
{
	return static_cast<ABI::Windows::UI::Xaml::IDependencyObject *>(m_base.Get())->GetValue(dp, returnValue);
}

STDMETHODIMP DependencyObject::SetValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable * value)
{
	return static_cast<ABI::Windows::UI::Xaml::IDependencyObject *>(m_base.Get())->SetValue(dp, value);
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
