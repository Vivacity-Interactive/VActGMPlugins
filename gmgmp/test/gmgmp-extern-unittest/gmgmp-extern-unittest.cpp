#include "pch.h"
#include "CppUnitTest.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <gmgmp/gmgmp.h>

#define _TEST_FN_NAME(In0) #In0
#define _TEST_LIB_DLL TEXT("gmvec2.dll")

namespace gmgmpunittest
{
	TEST_CLASS(gmgmpexternunittest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			typedef double (*_LPFN_GMGMP)(void);
			typedef double (*_LPFN_GMGMP_ARG)(double);

			const double life = 42;
			
			HINSTANCE h_lib = LoadLibrary(_TEST_LIB_DLL);
			Assert::IsNotNull(h_lib);

			_LPFN_GMGMP _lpfn = (_LPFN_GMGMP)GetProcAddress((HMODULE)h_lib, "_fn_gmgmp");
			Assert::IsTrue(_lpfn != nullptr);
			Assert::AreEqual(life, _lpfn());
			
			_LPFN_GMGMP_ARG _lpfn_arg = (_LPFN_GMGMP_ARG)GetProcAddress((HMODULE)h_lib, "_fn_gmgmp_arg");
			Assert::IsTrue(_lpfn_arg != nullptr);
			Assert::AreEqual(life, _lpfn_arg(life));

			FreeLibrary(h_lib);
		}

		TEST_METHOD(TestMethod2)
		{
			const double life = 42;

			HINSTANCE h_lib = LoadLibrary(_TEST_LIB_DLL);
			Assert::IsNotNull(h_lib);

			auto _lpfn = (decltype(&_fn_gmgmp))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(_fn_gmgmp));
			Assert::IsTrue(_lpfn != nullptr);
			Assert::AreEqual(life, _lpfn());

			auto _lpfn_arg = (decltype(&_fn_gmgmp_arg))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(_fn_gmgmp_arg));
			Assert::IsTrue(_lpfn_arg != nullptr);
			Assert::AreEqual(life, _lpfn_arg(life));

			FreeLibrary(h_lib);
		}

		TEST_METHOD(TestMPZ)
		{
			const double life = 42.0;
			const double death = 21.0;

			double a_real = 42;
			char a_string[] = "42";
			char b_string[] = "42";
			char neg_string[] = "-42";
			char n_string[] = "2";
			char m_string[] = "4242";
			

			HINSTANCE h_lib = LoadLibrary(_TEST_LIB_DLL);
			Assert::IsNotNull(h_lib);

			auto lpgmp_real = (decltype(&gmp_real))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_real));
			Assert::IsTrue(lpgmp_real != nullptr);
			Assert::AreEqual(life, lpgmp_real(a_string));

			auto lpgmp_string = (decltype(&gmp_string))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_string));
			Assert::IsTrue(lpgmp_string != nullptr);
			Assert::AreEqual("0x2a", lpgmp_string(a_real));

			auto lpgmp_tohex = (decltype(&gmp_tohex))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_tohex));
			Assert::IsTrue(lpgmp_tohex != nullptr);
			Assert::AreEqual("0x2a", lpgmp_tohex(a_string));

			auto lpgmp_todec = (decltype(&gmp_todec))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_todec));
			Assert::IsTrue(lpgmp_todec != nullptr);
			Assert::AreEqual("42", lpgmp_todec(a_string));

			auto lpgmp_add = (decltype(&gmp_add))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_add));
			Assert::IsTrue(lpgmp_add != nullptr);
			Assert::AreEqual("0x54", lpgmp_add(a_string, b_string));

			auto lpgmp_sub = (decltype(&gmp_sub))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_sub));
			Assert::IsTrue(lpgmp_sub != nullptr);
			Assert::AreEqual("0x0", lpgmp_sub(a_string, b_string));

			auto lpgmp_mul = (decltype(&gmp_mul))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_mul));
			Assert::IsTrue(lpgmp_mul != nullptr);
			Assert::AreEqual("0x6e4", lpgmp_mul(a_string, b_string));

			auto lpgmp_div = (decltype(&gmp_div))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_div));
			Assert::IsTrue(lpgmp_div != nullptr);
			Assert::AreEqual("0x1", lpgmp_div(a_string, b_string));

			auto lpgmp_mod = (decltype(&gmp_mod))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_mod));
			Assert::IsTrue(lpgmp_mod != nullptr);
			Assert::AreEqual("0x0", lpgmp_mod(a_string, b_string));

			auto lpgmp_neg = (decltype(&gmp_neg))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_neg));
			Assert::IsTrue(lpgmp_neg != nullptr);
			Assert::AreEqual("-0x2a", lpgmp_neg(a_string));

			auto lpgmp_abs = (decltype(&gmp_abs))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_abs));
			Assert::IsTrue(lpgmp_abs != nullptr);
			Assert::AreEqual("0x2a", lpgmp_abs(neg_string));

			auto lpgmp_pow = (decltype(&gmp_pow))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_pow));
			Assert::IsTrue(lpgmp_pow != nullptr);
			Assert::AreEqual("0x6e4", lpgmp_pow(a_string, n_string));

			auto lpgmp_powmod = (decltype(&gmp_powmod))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_powmod));
			Assert::IsTrue(lpgmp_powmod != nullptr);
			Assert::AreEqual("0x6e4", lpgmp_powmod(a_string, n_string, m_string));

			auto lpgmp_sqrt = (decltype(&gmp_sqrt))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_sqrt));
			Assert::IsTrue(lpgmp_sqrt != nullptr);
			Assert::AreEqual("0x6", lpgmp_sqrt(a_string));

			auto lpgmp_sqrtrem = (decltype(&gmp_sqrtrem))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_sqrtrem));
			Assert::IsTrue(lpgmp_sqrtrem != nullptr);
			Assert::AreEqual("0x6", lpgmp_sqrtrem(a_string));

			auto lpgmp_root = (decltype(&gmp_root))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_root));
			Assert::IsTrue(lpgmp_root != nullptr);
			Assert::AreEqual("0x6", lpgmp_root(a_string, n_string));

			auto lpgmp_rootrem = (decltype(&gmp_rootrem))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_rootrem));
			Assert::IsTrue(lpgmp_rootrem != nullptr);
			Assert::AreEqual("0x6", lpgmp_rootrem(a_string, n_string));

			auto lpgmp_compare = (decltype(&gmp_compare))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_compare));
			Assert::IsTrue(lpgmp_compare != nullptr);
			Assert::AreEqual(1.0, lpgmp_compare(a_string, neg_string));

			auto lpgmp_abscompare = (decltype(&gmp_abscompare))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_abscompare));
			Assert::IsTrue(lpgmp_abscompare != nullptr);
			Assert::AreEqual(0.0, lpgmp_abscompare(a_string, neg_string));

			auto lpgmp_sign = (decltype(&gmp_sign))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_sign));
			Assert::IsTrue(lpgmp_sign != nullptr);
			Assert::AreEqual(1.0, lpgmp_sign(a_string));

			auto lpgmp_even = (decltype(&gmp_even))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_even));
			Assert::IsTrue(lpgmp_even != nullptr);
			Assert::AreEqual(1.0, lpgmp_even(a_string));

			auto lpgmp_odd = (decltype(&gmp_odd))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_odd));
			Assert::IsTrue(lpgmp_odd != nullptr);
			Assert::AreEqual(0.0, lpgmp_odd(a_string));

			auto lpgmp_probab_prime = (decltype(&gmp_probab_prime))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_probab_prime));
			Assert::IsTrue(lpgmp_probab_prime != nullptr);
			Assert::AreEqual(0.0, lpgmp_probab_prime(a_string, death));

			auto lpgmp_probab_nextprime = (decltype(&gmp_probab_nextprime))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_probab_nextprime));
			Assert::IsTrue(lpgmp_probab_nextprime != nullptr);
			Assert::AreEqual("0x2b", lpgmp_probab_nextprime(a_string));

			auto lpgmp_gcd = (decltype(&gmp_gcd))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_gcd));
			Assert::IsTrue(lpgmp_gcd != nullptr);
			Assert::AreEqual("0x2a", lpgmp_gcd(a_string, b_string));

			auto lpgmp_lcm = (decltype(&gmp_lcm))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_lcm));
			Assert::IsTrue(lpgmp_lcm != nullptr);
			Assert::AreEqual("0x2a", lpgmp_lcm(a_string, b_string));

			auto lpgmp_factorial = (decltype(&gmp_factorial))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_factorial));
			Assert::IsTrue(lpgmp_factorial != nullptr);
			Assert::AreEqual("0x2", lpgmp_factorial(n_string));

			auto lpgmp_fibonacci = (decltype(&gmp_fibonacci))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_fibonacci));
			Assert::IsTrue(lpgmp_fibonacci != nullptr);
			Assert::AreEqual("0x1", lpgmp_fibonacci(n_string));

			auto lpgmp_min = (decltype(&gmp_min))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_min));
			Assert::IsTrue(lpgmp_min != nullptr);
			Assert::AreEqual("-0x2a", lpgmp_min(a_string, neg_string));

			auto lpgmp_max = (decltype(&gmp_max))GetProcAddress((HMODULE)h_lib, _TEST_FN_NAME(gmp_max));
			Assert::IsTrue(lpgmp_max != nullptr);
			Assert::AreEqual("0x2a", lpgmp_max(a_string, neg_string));


			FreeLibrary(h_lib);
		}
	};
}
