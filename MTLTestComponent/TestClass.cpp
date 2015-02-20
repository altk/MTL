#include "pch.h"
#include "TestClass.h"
#include "RuntimeClass.h"

using namespace mtl;
using namespace ABI::MTLTestComponent;
using namespace ABI::Windows::ApplicationModel::Background;

class TestClassImpl sealed : public RuntimeClass < IBackgroundTask >
{
public:
	virtual STDMETHODIMP GetRuntimeClassName(HSTRING * name) throw() override final
	{
		return WindowsCreateString(RuntimeClass_MTLTestComponent_TestTask, _countof(RuntimeClass_MTLTestComponent_TestTask), name);
	}
};
