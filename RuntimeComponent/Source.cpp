#include "pch.h"
#include "RuntimeComponent.h"
#include "MTL.h"
#include <cmath>

#include "functional"

using namespace MTL;
using namespace ABI::RuntimeComponent;
using ABI::Windows::ApplicationModel::Background::IBackgroundTask;
using ABI::Windows::ApplicationModel::Background::IBackgroundTaskInstance;

class ABI::RuntimeComponent::TestClass sealed : public RuntimeClass < ITestClass, ITestClass2 >
{
	INT32 value;
public:
	TestClass() throw() : value()
	{
	}

	explicit TestClass(INT32 value_) throw() : value(value_)
	{
	}

	TestClass(INT32 value_, INT32 power_) throw() : value(std::pow(value_, power_))
	{
	}

	STDMETHODIMP GetRuntimeClassName(HSTRING* className) throw() override final
	{
		return WindowsCreateString(
			RuntimeClass_RuntimeComponent_TestClass,
			_countof(RuntimeClass_RuntimeComponent_TestClass),
			className
			);
	}

	STDMETHODIMP get_Int(INT32* result) throw() override final
	{
		*result = value;
		return S_OK;
	}

	STDMETHODIMP get_Str(HSTRING* result) throw() override final
	{
		const WCHAR str[] = L"10";
		return WindowsCreateString(str, _countof(str), result);
	}

	STDMETHODIMP get_Long(INT64* result)
	{
		*result = value;
		return S_OK;
	}
};

class TestClassFactory sealed : public ActivationFactory < ITestClassFactory, TestClass >
{
public:
	static PCWSTR GetRuntimeClassName() throw()
	{
		return RuntimeClass_RuntimeComponent_TestClass;
	}

	STDMETHODIMP ActivateInstance(IInspectable** result)
	{
		return ActivateInstanceImpl(result);
	}

	STDMETHODIMP ActivateInstance0(INT32 value, ITestClass** result) throw() override final
	{
		return ActivateInstanceImpl(result, value);
	}

	STDMETHODIMP ActivateInstance1(INT32 value, INT32 power, ITestClass** result) throw() override final
	{
		return ActivateInstanceImpl(result, value, power);
	}
};

//Реализация экспортируемой функции получения фабрики объектов класса, имеющего идентификатор activatableClassId
HRESULT WINAPI DllGetActivationFactory(HSTRING activatableClassId, IActivationFactory** factory) throw()
{
	return Module<TestClassFactory>::GetModule().GetActivationFactory(activatableClassId, factory);
}

HRESULT WINAPI DllCanUnloadNow() throw()
{
	return S_OK;
	//return Module<TestClassFactory>::GetModule().CanUnload();
}
