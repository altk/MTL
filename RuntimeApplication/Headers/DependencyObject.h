#pragma once
#include <MTL.h>
#include <windows.ui.xaml.controls.h>

namespace RuntimeApplication
{
	class DependencyObject : public MTL::HeapClass < MTL::RuntimeClassBase<ABI::Windows::UI::Xaml::IDependencyObject> >
	{
	protected:
		MTL::ComPtr<IInspectable> m_inner;
		MTL::ComPtr<IInspectable> m_base;
	public:
		DependencyObject() noexcept = default;
		virtual ~DependencyObject() noexcept = default;

		static STDMETHODIMP ActivateInstance(DependencyObject**) noexcept;

		STDMETHODIMP GetRuntimeClassName(HSTRING * className) override;
		STDMETHODIMP GetValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable ** returnValue) override;
		STDMETHODIMP SetValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable * value) override;
		STDMETHODIMP ClearValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp) override;
		STDMETHODIMP ReadLocalValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable ** returnValue) override;
		STDMETHODIMP GetAnimationBaseValue(ABI::Windows::UI::Xaml::IDependencyProperty * dp, IInspectable ** returnValue) override;
		STDMETHODIMP get_Dispatcher(ABI::Windows::UI::Core::ICoreDispatcher ** value) override;
	};
}