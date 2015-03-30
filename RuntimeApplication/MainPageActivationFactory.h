#pragma once
#include <MTL.h>
#include "MainPage.xaml.h"

namespace RuntimeApplication
{
	class MainPageActivationFactory sealed : public MTL::ActivationFactory<ABI::RuntimeApplication::MainPage> 
	{
	public:
		STDMETHODIMP ActivateInstance(IInspectable**) noexcept override final;

		static PCWSTR GetRuntimeClassName() noexcept
		{
			return RuntimeClass_RuntimeApplication_MainPage;
		}
	};
}
