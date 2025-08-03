#include "pch.h"
#include "CppUnitTest.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <gmvec2/gmvec2.h>

#define _TEST_FN_NAME(In0) #In0
#define _TEST_LIB_DLL TEXT("gmvec2.dll")

namespace gmvec2unittest
{
	TEST_CLASS(gmvec2externunittest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			typedef double (*_LPFN)(void);
			typedef double (*_LPFN_ARG)(double);
			typedef void (*_LPFN_INTO)(double&);

			const double life = 42;

			HINSTANCE h_lib = LoadLibrary(_TEST_LIB_DLL);
			Assert::IsNotNull(h_lib);

			_LPFN _lpfn = (_LPFN)GetProcAddress((HMODULE)h_lib, "_fn_gmvec2");
			Assert::IsTrue(_lpfn != nullptr);
			Assert::AreEqual(life, _lpfn());

			_LPFN_ARG _lpfn_arg = (_LPFN_ARG)GetProcAddress((HMODULE)h_lib, "_fn_gmvec2_arg");
			Assert::IsTrue(_lpfn_arg != nullptr);
			Assert::AreEqual(life, _lpfn_arg(life));

			_LPFN_INTO _lpfn_into = (_LPFN_INTO)GetProcAddress((HMODULE)h_lib, "_fn_gmvec2_into");
			Assert::IsTrue(_lpfn_into != nullptr);
			double _life = 0.0;
			_lpfn_into(_life);
			Assert::AreEqual(life, _life);

			FreeLibrary(h_lib);
		}

		TEST_METHOD(TestMethod2)
		{
			const double life = 42;

			HINSTANCE h_lib = LoadLibrary(_TEST_LIB_DLL);
			Assert::IsNotNull(h_lib);

			auto _lpfn = (decltype(&_fn_gmvec2))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(_fn_gmvec2));
			Assert::IsTrue(_lpfn != nullptr);
			Assert::AreEqual(life, _lpfn());

			auto _lpfn_arg = (decltype(&_fn_gmvec2_arg))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(_fn_gmvec2_arg));
			Assert::IsTrue(_lpfn_arg != nullptr);
			Assert::AreEqual(life, _lpfn_arg(life));

			auto _lpfn_into = (decltype(&_fn_gmvec2_into))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(_fn_gmvec2_into));
			Assert::IsTrue(_lpfn_into != nullptr);
			double _life = 0.0;
			_lpfn_into(_life);
			Assert::AreEqual(life, _life);

			FreeLibrary(h_lib);
		}
	};
}
