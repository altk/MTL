#include "pch.h"
#include "RuntimeComponent.h"
#include "MTL.h"
#include <cmath>

using namespace MTL;
using namespace ABI::RuntimeComponent;
using ABI::Windows::ApplicationModel::Background::IBackgroundTask;
using ABI::Windows::ApplicationModel::Background::IBackgroundTaskInstance;

class ABI::RuntimeComponent::TestClass sealed : public RuntimeClass<ITestClass, ITestClass2>
{
	INT32 value;
public:
	TestClass() noexcept : value()
	{
	}

	explicit TestClass(INT32 value_) noexcept : value(value_)
	{
	}

	TestClass(INT32 value_, INT32 power_) noexcept : value(std::pow(value_, power_))
	{
	}

	STDMETHODIMP GetRuntimeClassName(HSTRING* className) noexcept override final
	{
		return WindowsCreateString(
			RuntimeClass_RuntimeComponent_TestClass,
			_countof(RuntimeClass_RuntimeComponent_TestClass),
			className
			);
	}

	STDMETHODIMP get_Int(INT32* result) noexcept override final
	{
		*result = value;
		return S_OK;
	}

	STDMETHODIMP get_Str(HSTRING* result) noexcept override final
	{
		const WCHAR str[] = L"10";
		return WindowsCreateString(str, _countof(str), result);
	}

	STDMETHODIMP get_Long(INT64* result) noexcept override final
	{
		*result = value;
		return S_OK;
	}
};

class TestClassFactory sealed : public ActivationFactory < TestClass, ITestClassFactory, ITestClassStatics >
{
public:
	static PCWSTR GetRuntimeClassName() noexcept
	{
		return RuntimeClass_RuntimeComponent_TestClass;
	}

	STDMETHODIMP ActivateInstance(IInspectable** result) noexcept override final
	{
		static_assert(sizeof(IInspectable) == sizeof(ITestClass), "Sizeof check failed");
		return ActivateInstanceImpl(reinterpret_cast<ITestClass**>(result));
	}

	STDMETHODIMP ActivateInstanceInt(INT32 value, ITestClass** result) noexcept override final
	{
		return ActivateInstanceImpl(result, value);
	}

	STDMETHODIMP ActivateInstanceIntInt(INT32 value, INT32 power, ITestClass** result) noexcept override final
	{
		return ActivateInstanceImpl(result, value, power);
	}

	STDMETHODIMP TryUnload() noexcept override final
	{
		CoFreeUnusedLibrariesEx(0, 0);
		return S_OK;
	}
};

//Реализация экспортируемой функции получения фабрики объектов класса, имеющего идентификатор activatableClassId
HRESULT WINAPI DllGetActivationFactory(HSTRING activatableClassId, IActivationFactory** factory) noexcept
{
	return Module<TestClassFactory>::GetModule().GetActivationFactory(activatableClassId, factory);
}

HRESULT WINAPI DllCanUnloadNow() noexcept
{
	return HeapAllocationStrategy::GetObjectCount() == 0 ? S_OK : S_FALSE;
}
