#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "gmvec2.h"
#include <string>
#include <cmath>

namespace gmvec2unittest
{
	struct _msg_utils_t
	{
		_msg_utils_t() = delete;

		template<typename T0>
		static void _log_val(const T0& value)
		{
			std::wstring _msg = L"testing value(" + std::to_wstring(pn) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<>
		static void _log_val(const float2_t& value)
		{
			std::wstring _msg = L"testing value(" + std::to_wstring(value.x) + L", " + std::to_wstring(value.y) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T0, typename T1>
		static void _log_pval_leq(T0 ex, T1 pn)
		{
			std::wstring _msg = L"testing expectation E[" + std::to_wstring(ex) + L"] <= p(" + std::to_wstring(pn) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T0, typename T1>
		static void _log_leq(const T0& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a) + L") <= b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T0, typename T1>
		static void _log_geq(const T0& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a) + L") >= b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T0, typename T1>
		static void _log_eq(const T0& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a) + L") == b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T0, typename T1>
		static void _log_impl(const T0& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a) + L") -> b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		static void _log_leq(const float2_t& a, const float2_t& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") <= b(" + std::to_wstring(b.x) + L", " + std::to_wstring(b.y) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		static void _log_geq(const float2_t& a, const float2_t& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") >= b(" + std::to_wstring(b.x) + L", " + std::to_wstring(b.y) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		static void _log_eq(const float2_t& a, const float2_t& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") == b(" + std::to_wstring(b.x) + L", " + std::to_wstring(b.y) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		static void _log_impl(const float2_t& a, const float2_t& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") -> b(" + std::to_wstring(b.x) + L", " + std::to_wstring(b.y) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T1>
		static void _log_leq(const float2_t& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") <= b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T1>
		static void _log_geq(const float2_t& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") >= b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T1>
		static void _log_eq(const float2_t& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") == b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}

		template<typename T1>
		static void _log_impl(const float2_t& a, const T1& b)
		{
			std::wstring _msg = L"testing bounds a(" + std::to_wstring(a.x) + L", " + std::to_wstring(a.y) + L") -> b(" + std::to_wstring(b) + L")\n";
			Logger::WriteMessage(_msg.c_str());
		}
	};

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
			char* _buf = nullptr, *_ref = nullptr;

			vec2_init_seed(_life);
			vec2_rnd(_death);
			vec2_rndr(_k, _n, _death);
			vec2_rndr2(_vec1._rep, _vec0._rep, _death);
			vec2_rndu(_death);
			vec2_rndur(_k, _n, _death);
			vec2_rndb(_death);
			vec2_rndswap(_vec._rep, _death);

			//Assert::IsNotNull(_buf = vec2_buffer(_n));
			//Assert::AreEqual(_N, vec2_buffer_capacity(_buf));
			//Assert::AreEqual(zero, vec2_buffer_count(_buf));
			//vec2_buffer_clear(_buf);
			//vec2_buffer_free(_buf);

		}

		TEST_METHOD(TestRndInitSeed)
		{
			size_t n = 42, k = 21;
			float2_t* vecs_n = (float2_t*)malloc(n * sizeof(float2_t));
			float2_t* vecs_k = (float2_t*)malloc(k * sizeof(float2_t));

			if (!vecs_n) { Assert::Fail(L"faild to allocate initial vedctor."); }

			const double _s0 = 0x0000000000000000ULL;
			const double _s1 = 0x3FF0000000000000ULL;
			const double _s2 = 0xA3F1C9B7E4D58239ULL;
			const double _s3 = 0x7D2A4EF9C0831B6EULL;

			const double _p0 = 1e-0, _p1 = 1e-1, _p2 = 1e-2, _p3 = 1e-3, _pn = 1e-16;

			{
				const double _s = _s0, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rnd(_q);
					_msg_utils_t::_log_geq(_vec, 0.0f);
					Assert::IsTrue(_vec.x >= 0.0f);
					Assert::IsTrue(_vec.y >= 0.0f);
					_msg_utils_t::_log_leq(_vec, 1.0f);
					Assert::IsTrue(_vec.x <= 1.0f);
					Assert::IsTrue(_vec.y <= 1.0f);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rnd(_q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rnd(_r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			{
				const double _s = _s1, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rnd(_q);
					Assert::IsTrue(_vec.x >= 0.0);
					Assert::IsTrue(_vec.y >= 0.0);
					Assert::IsTrue(_vec.x <= 1.0);
					Assert::IsTrue(_vec.y <= 1.0);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rnd(_q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rnd(_r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			{
				const double _s = _s2, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rnd(_q);
					Assert::IsTrue(_vec.x >= 0.0);
					Assert::IsTrue(_vec.y >= 0.0);
					Assert::IsTrue(_vec.x <= 1.0);
					Assert::IsTrue(_vec.y <= 1.0);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rnd(_q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rnd(_r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			{
				const double _s = _s2, _q = _s3, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rnd(_q);
					Assert::IsTrue(_vec.x >= 0.0);
					Assert::IsTrue(_vec.y >= 0.0);
					Assert::IsTrue(_vec.x <= 1.0);
					Assert::IsTrue(_vec.y <= 1.0);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rnd(_q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rnd(_r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			free(vecs_n);
			free(vecs_k);
		}

		TEST_METHOD(TestRndRange)
		{
			size_t n = 42, k = 21;
			float2_t* vecs_n = (float2_t*)malloc(n * sizeof(float2_t));
			float2_t* vecs_k = (float2_t*)malloc(k * sizeof(float2_t));

			if (!vecs_n) { Assert::Fail(L"faild to allocate initial vedctor."); }

			const double _s0 = 0x0000000000000000ULL;
			const double _s1 = 0x3FF0000000000000ULL;
			const double _s2 = 0xA3F1C9B7E4D58239ULL;
			const double _s3 = 0x7D2A4EF9C0831B6EULL;

			const double _p0 = 1e-0, _p1 = 1e-1, _p2 = 1e-2, _p3 = 1e-3, _pn = 1e-16;

			{
				const double _min = 21, _max = 42;
				const double _s = _s0, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rndr(_min, _max, _q);
					_msg_utils_t::_log_geq(_vec, float(_min));
					Assert::IsTrue(_vec.x >= float(_min));
					Assert::IsTrue(_vec.y >= float(_min));
					_msg_utils_t::_log_leq(_vec, float(_max));
					Assert::IsTrue(_vec.x <= float(_max));
					Assert::IsTrue(_vec.y <= float(_max));
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index){ Assert::AreEqual(vecs_n[index]._rep, vec2_rndr(_min, _max, _q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rndr(_min, _max, _r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			{
				float2_t _min{}, _max{}; _min.x = 21; _min.y = -42; _max.x = 42; _max.y = -21;
				const double _s = _s0, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rndr2(_min._rep, _max._rep, _q);
					_msg_utils_t::_log_geq(_vec, _min);
					Assert::IsTrue(_vec.x >= _min.x);
					Assert::IsTrue(_vec.y >= _min.y);
					_msg_utils_t::_log_leq(_vec, _max);
					Assert::IsTrue(_vec.x <= _max.x);
					Assert::IsTrue(_vec.y <= _max.y);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rndr2(_min._rep, _max._rep, _q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rndr2(_min._rep, _max._rep, _r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			free(vecs_n);
			free(vecs_k);
		}

		TEST_METHOD(TestRndUnit)
		{
			size_t n = 42, k = 21;
			float2_t* vecs_n = (float2_t*)malloc(n * sizeof(float2_t));
			float2_t* vecs_k = (float2_t*)malloc(k * sizeof(float2_t));

			if (!vecs_n) { Assert::Fail(L"faild to allocate initial vedctor."); }

			const double _s0 = 0x0000000000000000ULL;
			const double _s1 = 0x3FF0000000000000ULL;
			const double _s2 = 0xA3F1C9B7E4D58239ULL;
			const double _s3 = 0x7D2A4EF9C0831B6EULL;

			const double _p0 = 1e-0, _p1 = 1e-1, _p2 = 1e-2, _p3 = 1e-3, _pn = 1e-16;

			{
				const double _s = _s0, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rndu(_q);
					_msg_utils_t::_log_geq(_vec, -1.0f);
					Assert::IsTrue(_vec.x >= -1.0f);
					_msg_utils_t::_log_geq(_vec, 1.0f);
					Assert::IsTrue(_vec.x <= 1.0f);
					const float _len = sqrtf(_vec.x * _vec.x + _vec.y * _vec.y);
					const float _abs = fabsf(_len);
					_msg_utils_t::_log_leq(_len, 1.0f);
					Assert::IsTrue(_len <= 1.0f);
					_msg_utils_t::_log_geq(_len, -1.0f);
					Assert::IsTrue(_len >= -1.0f);
					Assert::IsTrue(_abs - 1.0f <= _pn);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rndu(_q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rndu(_r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			{
				const double _min = 21, _max = 42;
				const double _s = _s0, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rndur(_min, _max, _q);
					const float _len = sqrtf(_vec.x * _vec.x + _vec.y * _vec.y);
					const float _abs = fabsf(_len);
					_msg_utils_t::_log_leq(_len, float(_max));
					Assert::IsTrue(_len <= float(_max));
					_msg_utils_t::_log_geq(_len, -float(_min));
					Assert::IsTrue(_len >= -float(_min));
					Assert::IsTrue(_abs - float(_min) <= fabsf(float(_max - _min)));
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rndur(_min, _max, _q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rndur(_min, _max, _r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(_ex, _pn);
				Assert::IsTrue(_ex <= _pn);
			}

			free(vecs_n);
			free(vecs_k);
		}

		TEST_METHOD(TestRndSwapBool)
		{
			size_t n = 84, k = 21;
			float2_t* vecs_n = (float2_t*)malloc(n * sizeof(float2_t));
			float2_t* vecs_k = (float2_t*)malloc(k * sizeof(float2_t));

			if (!vecs_n) { Assert::Fail(L"faild to allocate initial vedctor."); }

			const double _s0 = 0x0000000000000000ULL;
			const double _s1 = 0x3FF0000000000000ULL;
			const double _s2 = 0xA3F1C9B7E4D58239ULL;
			const double _s3 = 0x7D2A4EF9C0831B6EULL;

			const double _p0 = 1e-0, _p1 = 1e-1, _p2 = 1e-2, _p3 = 1e-3, _pn = 1e-16;

			{
				const double _s = _s0, _q = _s0, _r = _s1;
				float2_t _vec0{}; _vec0.x = 21; _vec0.y = 42;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rndswap(_vec0._rep, _q);
					_msg_utils_t::_log_impl(_vec0, _vec);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rndswap(_vec0._rep, _q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rndswap(_vec0._rep, _r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(fabs(_ex - 0.5), _pn);
				Assert::IsTrue(fabs(_ex - 0.5) <= _pn);
			}

			{
				const double _s = _s0, _q = _s0, _r = _s1;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					float2_t& _vec = vecs_n[index];
					_vec._rep = vec2_rndb(_q);
					_msg_utils_t::_log_val(_vec);
				}
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index) { Assert::AreEqual(vecs_n[index]._rep, vec2_rndb(_q)); }

				double _ex = 0.0;
				vec2_init_seed(_s);
				for (size_t index = 0; index < n; ++index)
				{
					_ex += double(vecs_n[index]._rep == vec2_rndb(_r));
				}
				_ex /= double(n);
				_msg_utils_t::_log_pval_leq(fabs(_ex - 0.5), _pn);
				Assert::IsTrue(fabs(_ex - 0.5) <= _pn);
			}

			free(vecs_n);
			free(vecs_k);
		}
	};
}
