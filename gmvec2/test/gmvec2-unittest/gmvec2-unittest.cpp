#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "gmvec2.h"

namespace gmvec2unittest
{
	TEST_CLASS(gmvec2unittest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const double life = 42.0;
			Assert::AreEqual(life, _fn_gmvec2());
			Assert::AreEqual(life, _fn_gmvec2_arg(life));

			double _life = 0.0;
			_fn_gmvec2_into(_life);
			Assert::AreEqual(life, _life);
		}
	};
}
