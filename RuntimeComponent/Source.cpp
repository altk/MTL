#include "pch.h"
#include "RuntimeComponent.h"
#include "RuntimeClass.h"
#include <ObjIdlbase.h>

using namespace MTL;
using namespace ABI::RuntimeComponent;
using ABI::Windows::ApplicationModel::Background::IBackgroundTask;
using ABI::Windows::ApplicationModel::Background::IBackgroundTaskInstance;

struct ITest{};

class ABI::RuntimeComponent::TestBackgroundTask : public RuntimeClass < IBackgroundTask, ITestClass, ITest >
{
public:
	STDMETHODIMP GetRuntimeClassName(HSTRING * className) throw() override final
	{
		return WindowsCreateString(
			RuntimeClass_RuntimeComponent_TestBackgroundTask,
			_countof(RuntimeClass_RuntimeComponent_TestBackgroundTask),
			className
			);
	}

	STDMETHODIMP Run(IBackgroundTaskInstance *) throw() override final
	{
		//Просто пишем строку в отладочное окно
		OutputDebugStringW(L"Hello from background task.\r\n");
		return S_OK;
	}

	STDMETHODIMP get_Int(INT32 * result) throw() override final
	{
		*result = 10;
		return S_OK;
	}

	STDMETHODIMP get_Str(HSTRING * result) throw() override final
	{
		const WCHAR str[] = L"10";
		return WindowsCreateString(str, _countof(str), result);
	}
};

class TestBackgroundTaskFactory sealed : public RuntimeClass < IActivationFactory, IAgileObject >
{
public:
	STDMETHODIMP GetRuntimeClassName(HSTRING *) throw() override final
	{
		//Возвращаем данную константу, т.к. вызовается метод фабрики
		return E_ILLEGAL_METHOD_CALL;
	}

	//Реализация IActivationFactory метода инстанциирования экземпляра
	STDMETHODIMP ActivateInstance(IInspectable ** instance) throw() override final
	{
		//Если указатель равено null
		if (nullptr == instance)
		{
			//Возвращаем ошибку
			return E_INVALIDARG;
		}
		//Создаём объект 
		//При этом указываем признак того, что не надо генерировать исключение
		*instance = reinterpret_cast<IInspectable*>(new (std::nothrow) TestBackgroundTask());

		//Возвращаем результат в зависимости от успешности создания объекта
		return *instance ? S_OK : E_OUTOFMEMORY;
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
	if (0 == wcscmp(RuntimeClass_RuntimeComponent_TestBackgroundTask, WindowsGetStringRawBuffer(activatableClassId, nullptr)))
	{
		//Инициализируем указатель
		*factory = new (std::nothrow) TestBackgroundTaskFactory();
		return *factory ? S_OK : E_OUTOFMEMORY;
	}
	*factory = nullptr;
	return E_NOINTERFACE;
}

HRESULT WINAPI DllCanUnloadNow() throw()
{
	return S_OK;
}