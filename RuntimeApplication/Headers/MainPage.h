#pragma once
#include <MTL.h>
#include "MIDL\MainPage.xaml.h"

namespace ABI
{
	namespace RuntimeApplication
	{
		class MainPage sealed : public MTL::HeapClass < MTL::RuntimeClassBase < IMainPage,
			Windows::UI::Xaml::Markup::IComponentConnector,
			ABI::Windows::UI::Xaml::Controls::IPageOverrides,
			ABI::Windows::UI::Xaml::IUIElementOverrides,
			ABI::Windows::UI::Xaml::IFrameworkElementOverrides,
			ABI::Windows::UI::Xaml::Controls::IControlOverrides >>
		{
			using base = MTL::RuntimeClassBase<IMainPage,
				Windows::UI::Xaml::Markup::IComponentConnector,
				ABI::Windows::UI::Xaml::Controls::IPageOverrides,
				ABI::Windows::UI::Xaml::IUIElementOverrides,
				ABI::Windows::UI::Xaml::IFrameworkElementOverrides,
				ABI::Windows::UI::Xaml::Controls::IControlOverrides>;

			MTL::ComPtr<IInspectable> m_inner;
			MTL::ComPtr<ABI::Windows::UI::Xaml::Controls::IPageOverrides> m_pageOverrides;
			MTL::ComPtr<ABI::Windows::UI::Xaml::IUIElementOverrides> m_uiElementOverrides;
			MTL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElementOverrides> m_frameworkElementOverrides;
			MTL::ComPtr<ABI::Windows::UI::Xaml::Controls::IControlOverrides> m_controlOverrides;
		public:
			MainPage() noexcept;

			STDMETHODIMP QueryInterface(GUID const& id, void** object) noexcept override final
			{
				if (E_NOINTERFACE == base::QueryInterface(id, object))
				{
					if (m_inner)
					{
						auto hr = m_inner->QueryInterface(id, object);
						return hr;
					}
					return E_NOINTERFACE;
				}
				return S_OK;
			}
			STDMETHODIMP GetIids(ULONG* count, GUID** array) noexcept override final
			{
				ULONG innerCount;
				GUID* innerArray;

				m_inner->GetIids(&innerCount, &innerArray);

				CoTaskMemRealloc(static_cast<LPVOID>(innerArray), innerCount + BaseCountInterfaces());

				BaseGetIids(innerArray + innerCount);

				return S_OK;
			}
			STDMETHODIMP GetRuntimeClassName(HSTRING *result) noexcept override final
			{
				return WindowsCreateString(RuntimeClass_RuntimeApplication_MainPage, _countof(RuntimeClass_RuntimeApplication_MainPage), result);
			}
			STDMETHODIMP Connect(INT32, IInspectable *) noexcept override final
			{
				return S_OK;
			}

			STDMETHODIMP OnNavigatedTo(ABI::Windows::UI::Xaml::Navigation::INavigationEventArgs *e) noexcept override final
			{
				return S_OK;
			}

			STDMETHODIMP OnNavigatedFrom(ABI::Windows::UI::Xaml::Navigation::INavigationEventArgs *e) noexcept override final
			{
				return m_pageOverrides->OnNavigatedFrom(e);
			}

			STDMETHODIMP OnNavigatingFrom(ABI::Windows::UI::Xaml::Navigation::INavigatingCancelEventArgs *e) noexcept override final
			{
				return m_pageOverrides->OnNavigatingFrom(e);
			}

			STDMETHODIMP OnCreateAutomationPeer(ABI::Windows::UI::Xaml::Automation::Peers::IAutomationPeer **returnValue) noexcept override final
			{
				return m_uiElementOverrides->OnCreateAutomationPeer(returnValue);
			}

			STDMETHODIMP OnDisconnectVisualChildren(void) noexcept override final
			{
				return m_uiElementOverrides->OnDisconnectVisualChildren();
			}

			STDMETHODIMP FindSubElementsForTouchTargeting(ABI::Windows::Foundation::Point point, ABI::Windows::Foundation::Rect boundingRect, __FIIterable_1___FIIterable_1_Windows__CFoundation__CPoint **returnValue)  noexcept override final
			{
				return m_uiElementOverrides->FindSubElementsForTouchTargeting(point, boundingRect, returnValue);
			}

			STDMETHODIMP MeasureOverride(ABI::Windows::Foundation::Size availableSize, ABI::Windows::Foundation::Size *returnValue)  noexcept override final
			{
				return m_frameworkElementOverrides->MeasureOverride(availableSize, returnValue);
			}

			STDMETHODIMP ArrangeOverride(ABI::Windows::Foundation::Size finalSize, ABI::Windows::Foundation::Size *returnValue)  noexcept override final
			{
				return m_frameworkElementOverrides->ArrangeOverride(finalSize, returnValue);
			}

			STDMETHODIMP OnApplyTemplate(void) noexcept override final
			{
				return m_frameworkElementOverrides->OnApplyTemplate();
			}

			STDMETHODIMP OnPointerEntered(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerEntered(e);
			}

			STDMETHODIMP OnPointerPressed(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerPressed(e);
			}

			STDMETHODIMP OnPointerMoved(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerMoved(e);
			}

			STDMETHODIMP OnPointerReleased(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerReleased(e);
			}

			STDMETHODIMP OnPointerExited(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerExited(e);
			}

			STDMETHODIMP OnPointerCaptureLost(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerCaptureLost(e);
			}

			STDMETHODIMP OnPointerCanceled(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerCanceled(e);
			}

			STDMETHODIMP OnPointerWheelChanged(ABI::Windows::UI::Xaml::Input::IPointerRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnPointerWheelChanged(e);
			}

			STDMETHODIMP OnTapped(ABI::Windows::UI::Xaml::Input::ITappedRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnTapped(e);
			}

			STDMETHODIMP OnDoubleTapped(ABI::Windows::UI::Xaml::Input::IDoubleTappedRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnDoubleTapped(e);
			}

			STDMETHODIMP OnHolding(ABI::Windows::UI::Xaml::Input::IHoldingRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnHolding(e);
			}

			STDMETHODIMP OnRightTapped(ABI::Windows::UI::Xaml::Input::IRightTappedRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnRightTapped(e);
			}

			STDMETHODIMP OnManipulationStarting(ABI::Windows::UI::Xaml::Input::IManipulationStartingRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnManipulationStarting(e);
			}

			STDMETHODIMP OnManipulationInertiaStarting(ABI::Windows::UI::Xaml::Input::IManipulationInertiaStartingRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnManipulationInertiaStarting(e);
			}

			STDMETHODIMP OnManipulationStarted(ABI::Windows::UI::Xaml::Input::IManipulationStartedRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnManipulationStarted(e);
			}

			STDMETHODIMP OnManipulationDelta(ABI::Windows::UI::Xaml::Input::IManipulationDeltaRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnManipulationDelta(e);
			}

			STDMETHODIMP OnManipulationCompleted(ABI::Windows::UI::Xaml::Input::IManipulationCompletedRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnManipulationCompleted(e);
			}

			STDMETHODIMP OnKeyUp(ABI::Windows::UI::Xaml::Input::IKeyRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnKeyUp(e);
			}

			STDMETHODIMP OnKeyDown(ABI::Windows::UI::Xaml::Input::IKeyRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnKeyDown(e);
			}

			STDMETHODIMP OnGotFocus(ABI::Windows::UI::Xaml::IRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnGotFocus(e);
			}

			STDMETHODIMP OnLostFocus(ABI::Windows::UI::Xaml::IRoutedEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnLostFocus(e);
			}

			STDMETHODIMP OnDragEnter(ABI::Windows::UI::Xaml::IDragEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnDragEnter(e);
			}

			STDMETHODIMP OnDragLeave(ABI::Windows::UI::Xaml::IDragEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnDragLeave(e);
			}

			STDMETHODIMP OnDragOver(ABI::Windows::UI::Xaml::IDragEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnDragOver(e);
			}

			STDMETHODIMP OnDrop(ABI::Windows::UI::Xaml::IDragEventArgs *e) noexcept override final
			{
				return m_controlOverrides->OnDrop(e);
			}
		};
	}
}