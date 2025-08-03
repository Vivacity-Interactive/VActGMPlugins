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

		TEST_METHOD(TestVec2)
		{
			size_t n = 42, k = 21;
			size_t N = ((n + _VEC2_BUFFER_DELTA - 1) / _VEC2_BUFFER_DELTA) * n;
			size_t K = ((k + _VEC2_BUFFER_DELTA - 1) / _VEC2_BUFFER_DELTA) * k;

			float2_t _vec{}; _vec.x = -1.0f; _vec.y = 1.0f;
			float2_t _vec0{}; _vec0.x = 42.0f; _vec0.y = 21.0f;
			float2_t _vec1{}; _vec1.x = -42.0f; _vec1.y = -21.0f;
			double _life = 42, _death = -42;
			double _n = double(n), _k = double(k), _N = double(N), _K = double(K);
			double zero = 0.0, one = 1.0;
			char* _buf = nullptr, * _ref = nullptr;

			HINSTANCE h_lib = LoadLibrary(_TEST_LIB_DLL);
			Assert::IsNotNull(h_lib);

			auto lpgmp_init_seed = (decltype(&vec2_init_seed))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_init_seed));
			Assert::IsTrue(lpgmp_init_seed != nullptr);
			lpgmp_init_seed(_life);

			auto lpgmp_rnd = (decltype(&vec2_rnd))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_rnd));
			Assert::IsTrue(lpgmp_rnd != nullptr);
			lpgmp_rnd(_death);

			auto lpgmp_rndr = (decltype(&vec2_rndr))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_rndr));
			Assert::IsTrue(lpgmp_rnd != nullptr);
			lpgmp_rndr(_k, _n, _death);

			auto lpgmp_rndr2 = (decltype(&vec2_rndr2))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_rndr2));
			Assert::IsTrue(lpgmp_rndr2 != nullptr);
			lpgmp_rndr2(_vec1._rep, _vec0._rep, _death);

			auto lpgmp_rndu = (decltype(&vec2_rndu))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_rndu));
			Assert::IsTrue(lpgmp_rndu != nullptr);
			lpgmp_rndu(_death);

			auto lpgmp_rndur = (decltype(&vec2_rndur))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_rndur));
			Assert::IsTrue(lpgmp_rndur != nullptr);
			lpgmp_rndur(_k, _n, _death);

			auto lpgmp_rndb = (decltype(&vec2_rndb))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_rndb));
			Assert::IsTrue(lpgmp_rndb != nullptr);
			lpgmp_rndb(_death);

			auto lpgmp_rndswap = (decltype(&vec2_rndswap))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(vec2_rndswap));
			Assert::IsTrue(lpgmp_rndswap != nullptr);
			lpgmp_rndswap(_vec._rep, _death);
		}
	};
}
