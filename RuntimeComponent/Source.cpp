#include "pch.h"
#include "RuntimeComponent.h"
#include "RuntimeClass.h"
#include <ObjIdlbase.h>


using namespace MTL;
using namespace ABI::RuntimeComponent;
using ABI::Windows::ApplicationModel::Background::IBackgroundTask;
using ABI::Windows::ApplicationModel::Background::IBackgroundTaskInstance;

class ABI::RuntimeComponent::TestClass : public RuntimeClass < ITestClass >
{
	INT32 value;
public:
	explicit TestClass(INT32 value_) throw()
		: value(value_)
	{}

	STDMETHODIMP GetRuntimeClassName(HSTRING * className) throw() override final
	{
		return WindowsCreateString(
			RuntimeClass_RuntimeComponent_TestClass,
			_countof(RuntimeClass_RuntimeComponent_TestClass),
			className
			);
	}

	STDMETHODIMP get_Int(INT32 * result) throw() override final
	{
		*result = value;
		return S_OK;
	}

	STDMETHODIMP get_Str(HSTRING * result) throw() override final
	{
		const WCHAR str[] = L"10";
		return WindowsCreateString(str, _countof(str), result);
	}
};

class TestClassFactory sealed : public RuntimeClass < ITestClassFactory, IAgileObject, Cloaked<IActivationFactory> >
{
public:
	STDMETHODIMP GetRuntimeClassName(HSTRING *) throw() override final
	{
		//Возвращаем данную константу, т.к. вызовается метод фабрики
		return E_ILLEGAL_METHOD_CALL;
	}

	STDMETHODIMP ActivateInstance(IInspectable **)
	{
		return E_NOTIMPL;
	}

	//Реализация IActivationFactory метода инстанциирования экземпляра
	STDMETHODIMP ActivateInstance(INT32 value, ITestClass ** result) throw() override final
	{
		//Если указатель равено null
		if (nullptr == result)
		{
			//Возвращаем ошибку
			return E_INVALIDARG;
		}
		//Создаём объект 
		//При этом указываем признак того, что не надо генерировать исключение
		*result = new (std::nothrow) TestClass(value);

		//Возвращаем результат в зависимости от успешности создания объекта
		return *result ? S_OK : E_OUTOFMEMORY;
	}
};

//Реализация экспортируемой функции получения фабрики объектов класса, имеющего идентификатор activatableClassId
HRESULT WINAPI DllGetActivationFactory(HSTRING activatableClassId, IActivationFactory **factory) throw()
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
		*factory = new (std::nothrow) TestClassFactory();
		return *factory ? S_OK : E_OUTOFMEMORY;
	}
	*factory = nullptr;
	return E_NOINTERFACE;
}

HRESULT WINAPI DllCanUnloadNow() throw()
{
	return S_OK;
}