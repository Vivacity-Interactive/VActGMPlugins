#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "gmgmp.h"

namespace gmgmpunittest
{
	TEST_CLASS(gmgmpunittest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int life = 42;
			Assert::AreEqual(life, _fn_gmgmp());
			Assert::AreEqual(life, _fn_gmgmp_arg(life));
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

			Assert::AreEqual(life, gmp_real(a_string));
			Assert::AreEqual("0x2a", gmp_string(a_real));
			Assert::AreEqual("0x2a", gmp_tohex(a_string));
			Assert::AreEqual("42", gmp_todec(a_string));
			Assert::AreEqual("0x54", gmp_add(a_string, b_string));
			Assert::AreEqual("0x0", gmp_sub(a_string, b_string));
			Assert::AreEqual("0x6e4", gmp_mul(a_string, b_string));
			Assert::AreEqual("0x1", gmp_div(a_string, b_string));
			Assert::AreEqual("0x0", gmp_mod(a_string, b_string));
			Assert::AreEqual("-0x2a", gmp_neg(a_string));
			Assert::AreEqual("0x2a", gmp_abs(neg_string));
			Assert::AreEqual("0x6e4", gmp_pow(a_string, n_string));
			Assert::AreEqual("0x6e4", gmp_powmod(a_string, n_string, m_string));
			Assert::AreEqual("0x6", gmp_sqrt(a_string));
			Assert::AreEqual("0x6", gmp_sqrtrem(a_string));
			Assert::AreEqual("0x6", gmp_root(a_string, n_string));
			Assert::AreEqual("0x6", gmp_rootrem(a_string, n_string));
			Assert::AreEqual(1.0, gmp_compare(a_string, neg_string));
			Assert::AreEqual(0.0, gmp_abscompare(a_string, neg_string));
			Assert::AreEqual(1.0, gmp_sign(a_string));
			Assert::AreEqual(1.0, gmp_even(a_string));
			Assert::AreEqual(0.0, gmp_odd(a_string));
			Assert::AreEqual(0.0, gmp_probab_prime(a_string, death));
			Assert::AreEqual("0x2b", gmp_probab_nextprime(a_string));
			Assert::AreEqual("0x2a", gmp_gcd(a_string, b_string));
			Assert::AreEqual("0x2a", gmp_lcm(a_string, b_string));
			Assert::AreEqual("0x2", gmp_factorial(n_string));
			Assert::AreEqual("0x1", gmp_fibonacci(n_string));
			Assert::AreEqual("-0x2a", gmp_min(a_string, neg_string));
			Assert::AreEqual("0x2a", gmp_max(a_string, neg_string));
		}
	};
}
