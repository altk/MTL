#pragma once
#include <MTL.h>
#include "MainPage.h"

namespace RuntimeApplication
{
	class MainPageActivationFactory sealed : public MTL::ActivationFactory<ABI::RuntimeApplication::MainPage> 
	{
	public:
		STDMETHODIMP ActivateInstance(IInspectable **result) noexcept override final
		{
			return ActivateInstanceImpl(reinterpret_cast<ABI::RuntimeApplication::IMainPage **>(result));
		}

		static PCWSTR GetTargetRuntimeClassName() noexcept
		{
			return RuntimeClass_RuntimeApplication_MainPage;
		}
	};
}
