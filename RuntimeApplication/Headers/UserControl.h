#pragma once
#include <MTL.h>
#include <windows.ui.xaml.h>
#include <windows.ui.xaml.controls.h>

namespace RuntimeApplication
{
	class UserControl :public MTL::HeapClass < MTL::RuntimeClassBase <
		ABI::Windows::UI::Xaml::Controls::IUserControl,
		ABI::Windows::UI::Xaml::Controls::IControl,
		ABI::Windows::UI::Xaml::IUIElement,
		ABI::Windows::UI::Xaml::IDependencyObject >>
	{
	public:
		STDMETHODIMP GetRuntimeClassName(HSTRING* className) override { return S_OK; }
		STDMETHODIMP get_Content(ABI::Windows::UI::Xaml::IUIElement** value) override { return S_OK; }
		STDMETHODIMP put_Content(ABI::Windows::UI::Xaml::IUIElement* value) override { return S_OK; }
		STDMETHODIMP get_FontSize(DOUBLE* value) override { return S_OK; }
		STDMETHODIMP put_FontSize(DOUBLE value) override { return S_OK; }
		STDMETHODIMP get_FontFamily(ABI::Windows::UI::Xaml::Media::IFontFamily** value) override { return S_OK; }
		STDMETHODIMP put_FontFamily(ABI::Windows::UI::Xaml::Media::IFontFamily* value) override { return S_OK; }
		STDMETHODIMP get_FontWeight(ABI::Windows::UI::Text::FontWeight* value) override { return S_OK; }
		STDMETHODIMP put_FontWeight(ABI::Windows::UI::Text::FontWeight value) override { return S_OK; }
		STDMETHODIMP get_FontStyle(ABI::Windows::UI::Text::FontStyle* value) override { return S_OK; }
		STDMETHODIMP put_FontStyle(ABI::Windows::UI::Text::FontStyle value) override { return S_OK; }
		STDMETHODIMP get_FontStretch(ABI::Windows::UI::Text::FontStretch* value) override { return S_OK; }
		STDMETHODIMP put_FontStretch(ABI::Windows::UI::Text::FontStretch value) override { return S_OK; }
		STDMETHODIMP get_CharacterSpacing(INT32* value) override { return S_OK; }
		STDMETHODIMP put_CharacterSpacing(INT32 value) override { return S_OK; }
		STDMETHODIMP get_Foreground(ABI::Windows::UI::Xaml::Media::IBrush** value) override { return S_OK; }
		STDMETHODIMP put_Foreground(ABI::Windows::UI::Xaml::Media::IBrush* value) override { return S_OK; }
		STDMETHODIMP get_IsTabStop(boolean* value) override { return S_OK; }
		STDMETHODIMP put_IsTabStop(boolean value) override { return S_OK; }
		STDMETHODIMP get_IsEnabled(boolean* value) override { return S_OK; }
		STDMETHODIMP put_IsEnabled(boolean value) override { return S_OK; }
		STDMETHODIMP get_TabIndex(INT32* value) override { return S_OK; }
		STDMETHODIMP put_TabIndex(INT32 value) override { return S_OK; }
		STDMETHODIMP get_TabNavigation(ABI::Windows::UI::Xaml::Input::KeyboardNavigationMode* value) override { return S_OK; }
		STDMETHODIMP put_TabNavigation(ABI::Windows::UI::Xaml::Input::KeyboardNavigationMode value) override { return S_OK; }
		STDMETHODIMP get_Template(ABI::Windows::UI::Xaml::Controls::IControlTemplate** value) override { return S_OK; }
		STDMETHODIMP put_Template(ABI::Windows::UI::Xaml::Controls::IControlTemplate* value) override { return S_OK; }
		STDMETHODIMP get_Padding(ABI::Windows::UI::Xaml::Thickness* value) override { return S_OK; }
		STDMETHODIMP put_Padding(ABI::Windows::UI::Xaml::Thickness value) override { return S_OK; }
		STDMETHODIMP get_HorizontalContentAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment* value) override { return S_OK; }
		STDMETHODIMP put_HorizontalContentAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment value) override { return S_OK; }
		STDMETHODIMP get_VerticalContentAlignment(ABI::Windows::UI::Xaml::VerticalAlignment* value) override { return S_OK; }
		STDMETHODIMP put_VerticalContentAlignment(ABI::Windows::UI::Xaml::VerticalAlignment value) override { return S_OK; }
		STDMETHODIMP get_Background(ABI::Windows::UI::Xaml::Media::IBrush** value) override { return S_OK; }
		STDMETHODIMP put_Background(ABI::Windows::UI::Xaml::Media::IBrush* value) override { return S_OK; }
		STDMETHODIMP get_BorderThickness(ABI::Windows::UI::Xaml::Thickness* value) override { return S_OK; }
		STDMETHODIMP put_BorderThickness(ABI::Windows::UI::Xaml::Thickness value) override { return S_OK; }
		STDMETHODIMP get_BorderBrush(ABI::Windows::UI::Xaml::Media::IBrush** value) override { return S_OK; }
		STDMETHODIMP put_BorderBrush(ABI::Windows::UI::Xaml::Media::IBrush* value) override { return S_OK; }
		STDMETHODIMP get_FocusState(ABI::Windows::UI::Xaml::FocusState* value) override { return S_OK; }
		STDMETHODIMP add_IsEnabledChanged(ABI::Windows::UI::Xaml::IDependencyPropertyChangedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_IsEnabledChanged(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP ApplyTemplate(boolean* returnValue) override { return S_OK; }
		STDMETHODIMP Focus(ABI::Windows::UI::Xaml::FocusState value, boolean* returnValue) override { return S_OK; }
		STDMETHODIMP GetValue(ABI::Windows::UI::Xaml::IDependencyProperty* dp, IInspectable** returnValue) override { return S_OK; }
		STDMETHODIMP SetValue(ABI::Windows::UI::Xaml::IDependencyProperty* dp, IInspectable* value) override { return S_OK; }
		STDMETHODIMP ClearValue(ABI::Windows::UI::Xaml::IDependencyProperty* dp) override { return S_OK; }
		STDMETHODIMP ReadLocalValue(ABI::Windows::UI::Xaml::IDependencyProperty* dp, IInspectable** returnValue) override { return S_OK; }
		STDMETHODIMP GetAnimationBaseValue(ABI::Windows::UI::Xaml::IDependencyProperty* dp, IInspectable** returnValue) override { return S_OK; }
		STDMETHODIMP get_Dispatcher(ABI::Windows::UI::Core::ICoreDispatcher** value) override { return S_OK; }
		STDMETHODIMP get_DesiredSize(ABI::Windows::Foundation::Size* value) override { return S_OK; }
		STDMETHODIMP get_AllowDrop(boolean* value) override { return S_OK; }
		STDMETHODIMP put_AllowDrop(boolean value) override { return S_OK; }
		STDMETHODIMP get_Opacity(DOUBLE* value) override { return S_OK; }
		STDMETHODIMP put_Opacity(DOUBLE value) override { return S_OK; }
		STDMETHODIMP get_Clip(ABI::Windows::UI::Xaml::Media::IRectangleGeometry** value) override { return S_OK; }
		STDMETHODIMP put_Clip(ABI::Windows::UI::Xaml::Media::IRectangleGeometry* value) override { return S_OK; }
		STDMETHODIMP get_RenderTransform(ABI::Windows::UI::Xaml::Media::ITransform** value) override { return S_OK; }
		STDMETHODIMP put_RenderTransform(ABI::Windows::UI::Xaml::Media::ITransform* value) override { return S_OK; }
		STDMETHODIMP get_Projection(ABI::Windows::UI::Xaml::Media::IProjection** value) override { return S_OK; }
		STDMETHODIMP put_Projection(ABI::Windows::UI::Xaml::Media::IProjection* value) override { return S_OK; }
		STDMETHODIMP get_RenderTransformOrigin(ABI::Windows::Foundation::Point* value) override { return S_OK; }
		STDMETHODIMP put_RenderTransformOrigin(ABI::Windows::Foundation::Point value) override { return S_OK; }
		STDMETHODIMP get_IsHitTestVisible(boolean* value) override { return S_OK; }
		STDMETHODIMP put_IsHitTestVisible(boolean value) override { return S_OK; }
		STDMETHODIMP get_Visibility(ABI::Windows::UI::Xaml::Visibility* value) override { return S_OK; }
		STDMETHODIMP put_Visibility(ABI::Windows::UI::Xaml::Visibility value) override { return S_OK; }
		STDMETHODIMP get_RenderSize(ABI::Windows::Foundation::Size* value) override { return S_OK; }
		STDMETHODIMP get_UseLayoutRounding(boolean* value) override { return S_OK; }
		STDMETHODIMP put_UseLayoutRounding(boolean value) override { return S_OK; }
		STDMETHODIMP get_Transitions(ABI::Windows::Foundation::Collections::__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_t** value) override { return S_OK; }
		STDMETHODIMP put_Transitions(ABI::Windows::Foundation::Collections::__FIVector_1_Windows__CUI__CXaml__CMedia__CAnimation__CTransition_t* value) override { return S_OK; }
		STDMETHODIMP get_CacheMode(ABI::Windows::UI::Xaml::Media::ICacheMode** value) override { return S_OK; }
		STDMETHODIMP put_CacheMode(ABI::Windows::UI::Xaml::Media::ICacheMode* value) override { return S_OK; }
		STDMETHODIMP get_IsTapEnabled(boolean* value) override { return S_OK; }
		STDMETHODIMP put_IsTapEnabled(boolean value) override { return S_OK; }
		STDMETHODIMP get_IsDoubleTapEnabled(boolean* value) override { return S_OK; }
		STDMETHODIMP put_IsDoubleTapEnabled(boolean value) override { return S_OK; }
		STDMETHODIMP get_IsRightTapEnabled(boolean* value) override { return S_OK; }
		STDMETHODIMP put_IsRightTapEnabled(boolean value) override { return S_OK; }
		STDMETHODIMP get_IsHoldingEnabled(boolean* value) override { return S_OK; }
		STDMETHODIMP put_IsHoldingEnabled(boolean value) override { return S_OK; }
		STDMETHODIMP get_ManipulationMode(ABI::Windows::UI::Xaml::Input::ManipulationModes* value) override { return S_OK; }
		STDMETHODIMP put_ManipulationMode(ABI::Windows::UI::Xaml::Input::ManipulationModes value) override { return S_OK; }
		STDMETHODIMP get_PointerCaptures(ABI::Windows::Foundation::Collections::__FIVectorView_1_Windows__CUI__CXaml__CInput__CPointer_t** value) override { return S_OK; }
		STDMETHODIMP add_KeyUp(ABI::Windows::UI::Xaml::Input::IKeyEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_KeyUp(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_KeyDown(ABI::Windows::UI::Xaml::Input::IKeyEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_KeyDown(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_GotFocus(ABI::Windows::UI::Xaml::IRoutedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_GotFocus(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_LostFocus(ABI::Windows::UI::Xaml::IRoutedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_LostFocus(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_DragEnter(ABI::Windows::UI::Xaml::IDragEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_DragEnter(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_DragLeave(ABI::Windows::UI::Xaml::IDragEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_DragLeave(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_DragOver(ABI::Windows::UI::Xaml::IDragEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_DragOver(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_Drop(ABI::Windows::UI::Xaml::IDragEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_Drop(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerPressed(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerPressed(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerMoved(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerMoved(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerReleased(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerReleased(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerEntered(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerEntered(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerExited(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerExited(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerCaptureLost(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerCaptureLost(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerCanceled(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerCanceled(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_PointerWheelChanged(ABI::Windows::UI::Xaml::Input::IPointerEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_PointerWheelChanged(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_Tapped(ABI::Windows::UI::Xaml::Input::ITappedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_Tapped(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_DoubleTapped(ABI::Windows::UI::Xaml::Input::IDoubleTappedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_DoubleTapped(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_Holding(ABI::Windows::UI::Xaml::Input::IHoldingEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_Holding(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_RightTapped(ABI::Windows::UI::Xaml::Input::IRightTappedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_RightTapped(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_ManipulationStarting(ABI::Windows::UI::Xaml::Input::IManipulationStartingEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_ManipulationStarting(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_ManipulationInertiaStarting(ABI::Windows::UI::Xaml::Input::IManipulationInertiaStartingEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_ManipulationInertiaStarting(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_ManipulationStarted(ABI::Windows::UI::Xaml::Input::IManipulationStartedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_ManipulationStarted(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_ManipulationDelta(ABI::Windows::UI::Xaml::Input::IManipulationDeltaEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_ManipulationDelta(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP add_ManipulationCompleted(ABI::Windows::UI::Xaml::Input::IManipulationCompletedEventHandler* value, EventRegistrationToken* token) override { return S_OK; }
		STDMETHODIMP remove_ManipulationCompleted(EventRegistrationToken token) override { return S_OK; }
		STDMETHODIMP Measure(ABI::Windows::Foundation::Size availableSize) override { return S_OK; }
		STDMETHODIMP Arrange(ABI::Windows::Foundation::Rect finalRect) override { return S_OK; }
		STDMETHODIMP CapturePointer(ABI::Windows::UI::Xaml::Input::IPointer* value, boolean* returnValue) override { return S_OK; }
		STDMETHODIMP ReleasePointerCapture(ABI::Windows::UI::Xaml::Input::IPointer* value) override { return S_OK; }
		STDMETHODIMP ReleasePointerCaptures() override { return S_OK; }
		STDMETHODIMP AddHandler(ABI::Windows::UI::Xaml::IRoutedEvent* routedEvent, IInspectable* handler, boolean handledEventsToo) override { return S_OK; }
		STDMETHODIMP RemoveHandler(ABI::Windows::UI::Xaml::IRoutedEvent* routedEvent, IInspectable* handler) override { return S_OK; }
		STDMETHODIMP TransformToVisual(ABI::Windows::UI::Xaml::IUIElement* visual, ABI::Windows::UI::Xaml::Media::IGeneralTransform** returnValue) override { return S_OK; }
		STDMETHODIMP InvalidateMeasure() override { return S_OK; }
		STDMETHODIMP InvalidateArrange() override { return S_OK; }
		STDMETHODIMP UpdateLayout() override { return S_OK; }
	protected:
		MTL::ComPtr<IInspectable> m_inner;
		MTL::ComPtr<IInspectable> m_base;
	public:
		static STDMETHODIMP ActivateInstance(UserControl **) noexcept;
	};
}