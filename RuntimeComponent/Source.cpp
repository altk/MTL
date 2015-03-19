#include "pch.h"
#include "RuntimeComponent.h"
#include "MTL.h"
#include <cmath>

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

class TestClassFactory sealed : public ActivationFactory < ITestClassFactory >
{
public:
	STDMETHODIMP ActivateInstance(IInspectable** result)
	{
		return ActivateInstanceImpl<TestClass>(result);
	}

	STDMETHODIMP ActivateInstance0(INT32 value, ITestClass** result) throw() override final
	{
		return ActivateInstanceImpl<TestClass>(result, value);
	}

	STDMETHODIMP ActivateInstance1(INT32 value, INT32 power, ITestClass** result) throw() override final
	{
		return ActivateInstanceImpl<TestClass>(result, value, power);
	}
};

//Реализация экспортируемой функции получения фабрики объектов класса, имеющего идентификатор activatableClassId
HRESULT WINAPI DllGetActivationFactory(HSTRING activatableClassId, IActivationFactory** factory) throw()
{
	//Проверяем идентфикатор класса и указатель на фабрику
	if (WindowsIsStringEmpty(activatableClassId) || nullptr == factory)
	{
		//Если идентификатор не задан или указатель нулевой
		return E_INVALIDARG;
	}
	//Проверяем на равенство строки идентификатора класса и определенного нами класса
	if (0 == wcscmp(RuntimeClass_RuntimeComponent_TestClass, WindowsGetStringRawBuffer(activatableClassId, nullptr)))
	{
		//Инициализируем указатель
		*factory = new(std::nothrow) TestClassFactory();
		return *factory ? S_OK : E_OUTOFMEMORY;
	}
	*factory = nullptr;
	return E_NOINTERFACE;
}

HRESULT WINAPI DllCanUnloadNow() throw()
{
	return Module::GetModule().CanUnload();
}
