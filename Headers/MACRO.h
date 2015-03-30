#include <Windows.h>
#include <stdio.h>
#include <crtdbg.h>

#define ASSERT _ASSERTE

#ifdef _DEBUG
struct Tracer
{
	char const * m_filename;
	unsigned m_line;

	Tracer(char const * filename, unsigned const line) noexcept
		: m_filename(filename)
		, m_line(line)
	{

	}

	void operator()(wchar_t const * format, ...) const noexcept
	{
		wchar_t buffer[512];
		auto count = swprintf_s(buffer, L"%S(%d): ", m_filename, m_line);

		ASSERT(-1 != count);

		va_list args;
		va_start(args, format);
		ASSERT(-1 != _vsnwprintf_s(buffer + count, _countof(buffer) - count, _countof(buffer) - count - 1, format, args));
		va_end(args);

		OutputDebugString(buffer);
	}
};
#endif

#ifdef _DEBUG
#define TRACE Tracer(__FILE__, __LINE__)
#else
#define TRACE __noop
#endif

#ifdef _DEBUG
#define VERIFY ASSERT
#else
#define VERIFY(expression) (expression)
#endif

#ifdef _DEBUG
#define VERIFY_SUCCEEDED(expression) ASSERT(SUCCEEDED(expression))
#else
#define VERIFY_SUCCEEDED(expression) (expression)
#endif