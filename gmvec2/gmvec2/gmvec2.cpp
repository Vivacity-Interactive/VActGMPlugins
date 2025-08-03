// gmvec2.cpp : Defines the functions for the static library.
//

#include "pch.h"
//#include "stdlib.h"

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <random>
#include <cmath>
#include <limits>
#include "gmvec2.h"

#define _VEC2_SEED_0 0x123456789ABCDEF0ULL
#define _VEC2_SEED_1 0x9E3779B97F4A7C15ULL 
#define _VEC2_SEED_2 0x2545F4914F6CDD1DULL
#define _VEC2_SEED_3 0x85EBCA77C2B2AE63ULL
#define _VEC2_SEED_4 0xBADC0FFEE0DDF00DULL

#define _VEC2_PI (3.14159265358979323846264338327950288419716939937510582097494459230781640628f)
#define _VEC2_EPS_0 (1.e-8f)
#define _VEC2_EPS_1 (1.e-4f)

uint64_t _vec2_seed = _VEC2_SEED_0;

uint64_t _vec2_seed_combine(double seed = 0.0)
{
	uint64_t _seed = static_cast<uint64_t>(seed);
	_vec2_seed ^= (_seed + _VEC2_SEED_1 + (_vec2_seed << 6) + (_seed >> 2));
	_vec2_seed *= _VEC2_SEED_2;
	_vec2_seed += _VEC2_SEED_3;
	return _vec2_seed;
}

uint64_t _vec2_rnd_next(double seed = 0.0)
{
	uint64_t _seed = _vec2_seed_combine(seed);
	_seed ^= _seed >> 12;
	_seed ^= _seed << 25;
	_seed ^= _seed >> 27;
	_vec2_seed = _seed * _VEC2_SEED_2 + _VEC2_SEED_3;
	return _vec2_seed;
}

inline float _vec2_rnd_next_float(double seed = 0.0)
{
	return _vec2_rnd_next(seed) * (1.0f / (std::numeric_limits<uint64_t>::max() + 1.0));
}

inline float _vec2_rnd_next_float_range(double min, double max, double seed = 0.0)
{
	return static_cast<float>(min + _vec2_rnd_next_float(seed) * (max - min));
}

GMVEC2_API double _fn_gmvec2()
{
	return 42.0;
}

GMVEC2_API double _fn_gmvec2_arg(double arg)
{
	return arg;
}

GMVEC2_API void _fn_gmvec2_into(double& into)
{
	into = 42.0;
}

GMVEC2_API void vec2_init_seed(double seed)
{
	_vec2_seed = _VEC2_SEED_0 ^ static_cast<uint64_t>(seed);
}

GMVEC2_API void vec2_buffer_free(char* ptr_buffer)
{
	if (ptr_buffer) { reinterpret_cast<floats2_t*>(ptr_buffer)->~buffer_t(); free(ptr_buffer); }
}

GMVEC2_API char* vec2_buffer(double capacity)
{
	floats2_t* ptr_buffer = (floats2_t*)std::malloc(sizeof(floats2_t));
	if (!ptr_buffer) { return nullptr; }
	ptr_buffer->resize(size_t(capacity));
	return ptr_buffer->_buf;
}

GMVEC2_API double vec2_buffer_count(char* ptr_buffer)
{
	return ptr_buffer ? static_cast<double>(reinterpret_cast<floats2_t*>(ptr_buffer)->size()) : 0;
}

GMVEC2_API double vec2_buffer_capacity(char* ptr_buffer)
{
	return ptr_buffer ? static_cast<double>(reinterpret_cast<floats2_t*>(ptr_buffer)->size_buffer()) : 0;
}

GMVEC2_API void vec2_buffer_clear(char* ptr_buffer)
{
	if (ptr_buffer) { reinterpret_cast<floats2_t*>(ptr_buffer)->clear(); }
}

GMVEC2_API void vec2_buffer_clear2(char* ptr_buffer, double count)
{
	if (ptr_buffer) { reinterpret_cast<floats2_t*>(ptr_buffer)->clear(size_t(count)); }
}


GMVEC2_API void vec2_buffer_push(char* ptr_buffer, double vec)
{
	if (ptr_buffer)
	{
		float2_t& _vec = reinterpret_cast<float2_t&>(vec);
		reinterpret_cast<floats2_t*>(ptr_buffer)->push(_vec);
	}
}

GMVEC2_API double vec2_buffer_pop(char* ptr_buffer)
{
	return ptr_buffer ? reinterpret_cast<floats2_t*>(ptr_buffer)->pop()._rep : 0.0;
}

GMVEC2_API void vec2_buffer_pop2(char* ptr_buffer, char* ptr_vec)
{
	if (ptr_buffer && ptr_vec)
	{
		*reinterpret_cast<float2_t*>(ptr_vec) = reinterpret_cast<floats2_t*>(ptr_buffer)->pop();
	}
}

GMVEC2_API char* vec2_buffer_get(double index, char* ptr_buffer)
{
	return ptr_buffer ? reinterpret_cast<char*>(reinterpret_cast<floats2_t*>(ptr_buffer)->get(size_t(index))) : nullptr;
}

GMVEC2_API void vec2_buffer_set(double index, char* ptr_buffer, double vec)
{
	if (ptr_buffer)
	{
		(*reinterpret_cast<floats2_t*>(ptr_buffer))[size_t(index)]._rep = vec;
	}
}

GMVEC2_API double vec2_buffer_at(double index, char* ptr_buffer)
{
	return ptr_buffer ? (*reinterpret_cast<floats2_t*>(ptr_buffer))[size_t(index)]._rep : 0.0;
}

GMVEC2_API void vec2_buffer_at2(double index, char* ptr_buffer, char* ptr_vec)
{
	if (ptr_buffer && ptr_vec)
	{
		*reinterpret_cast<float2_t*>(ptr_vec) = (*reinterpret_cast<floats2_t*>(ptr_buffer))[size_t(index)];
	}
}

GMVEC2_API char* vec2_ptr(double vec)
{
	float2_t* ptr_vec = (float2_t*)std::malloc(sizeof(float2_t));
	if (!ptr_vec) { return nullptr; }
	ptr_vec->_rep = vec;
	return ptr_vec->_buf;
}

GMVEC2_API char* vec2_ptr2(double x, double y)
{
	float2_t* ptr_vec = (float2_t*)std::malloc(sizeof(float2_t));
	if (!ptr_vec) { return nullptr; }
	ptr_vec->x = static_cast<float>(x);
	ptr_vec->y = static_cast<float>(y);
	return ptr_vec->_buf;
}

GMVEC2_API double vec2_vec(char* ptr_vec)
{
	return ((float2_t*)ptr_vec)->_rep;
}

GMVEC2_API void vec2_into(char* ptr_vec, double vec)
{
	((float2_t*)ptr_vec)->_rep = vec;
}

GMVEC2_API void vec2_into2(char* ptr_vec, double x, double y)
{
	float2_t _vec{ *reinterpret_cast<double*>(ptr_vec) };
	_vec.x = static_cast<float>(x);
	_vec.y = static_cast<float>(y);
}

GMVEC2_API double vec2_swap(char* ptr_lhs, char* ptr_rhs)
{
	float2_t& _lhs = *((float2_t*)ptr_lhs);
	float2_t& _rhs = *((float2_t*)ptr_rhs);
	double _tmp = _lhs._rep; _lhs._rep = _rhs._rep; _rhs._rep = _tmp;
	return _lhs._rep;
}

GMVEC2_API void vec2_free(char* ptr_vec)
{
	if (ptr_vec) { free(ptr_vec); }
}

GMVEC2_API double vec2_rnd(double seed)
{
	float2_t _vec{};
	_vec.x = _vec2_rnd_next_float(seed);
	_vec.y = _vec2_rnd_next_float(seed);
	return _vec._rep;
}

GMVEC2_API double vec2_rndr(double min, double max, double seed)
{
	float2_t _vec{};
	_vec.x = _vec2_rnd_next_float_range(min, max, seed);
	_vec.y = _vec2_rnd_next_float_range(min, max, seed);
	return _vec._rep;
}

GMVEC2_API double vec2_rndr2(double vmin, double vmax, double seed)
{
	float2_t _vec{}, _min{ vmin }, _max{ vmax };
	_vec.x = _vec2_rnd_next_float_range(static_cast<double>(_min.x), static_cast<double>(_max.x), seed);
	_vec.y = _vec2_rnd_next_float_range(static_cast<double>(_min.y), static_cast<double>(_max.y), seed);
	return _vec._rep;
}

GMVEC2_API double vec2_rndu(double seed)
{
	float2_t _vec{};
	float _angle = _vec2_rnd_next_float(seed) * 2.0f * _VEC2_PI;
	_vec.x = std::cosf(_angle);
	_vec.y = std::sinf(_angle);
	return _vec._rep;
}

GMVEC2_API double vec2_rndur(double min, double max, double seed)
{
	float2_t _vec{};
	float _angle = _vec2_rnd_next_float(seed) * 2.0f * _VEC2_PI;
	float _norm = _vec2_rnd_next_float_range(min, max, seed);
	_vec.x = std::cosf(_angle) * _norm;
	_vec.y = std::sinf(_angle) * _norm;
	return _vec._rep;
}

GMVEC2_API double vec2_rndb(double seed)
{
	float2_t _vec{};
	uint32_t bx = static_cast<uint32_t>(_vec2_rnd_next(seed + _VEC2_SEED_4)) >> 31;
	_vec.x = float(bx);
	_vec.y = float(1.0f - bx);
	return _vec._rep;
}

GMVEC2_API double vec2_rndbr(double min, double max, double seed)
{
	float2_t _vec{};
	float bx = static_cast<float>(static_cast<uint32_t>(_vec2_rnd_next(seed + _VEC2_SEED_4)) >> 31);
	float _norm = _vec2_rnd_next_float_range(min, max, seed);
	_vec.x = bx * _norm;
	_vec.y = (1.0f - bx) * _norm;
	return _vec._rep;
}

GMVEC2_API double vec2_rndswap(double vec, double seed)
{
	float2_t _vec{ vec }, _temp{ vec };
	float b1 = static_cast<float>(static_cast<uint32_t>(_vec2_rnd_next(seed + _VEC2_SEED_4)) >> 31);
	float b0 = 1.0f - b1;
	_vec.x = b1 * _temp.y + b0 * _temp.x;
	_vec.y = b0 * _temp.y + b1 * _temp.x;
	return _vec._rep;
}

GMVEC2_API double vec2_x(double vec)
{
	float2_t _vec{ vec };
	return _vec.x;
}

GMVEC2_API double vec2_y(double vec)
{
	float2_t _vec{ vec };
	return _vec.y;
}

GMVEC2_API double vec2_new(double x, double y)
{
	float2_t _vec{};
	_vec.x = static_cast<float>(x);
	_vec.y = static_cast<float>(y);
	return _vec._rep;
}

GMVEC2_API double vec2_newx(double a)
{
	float2_t _vec{};
	_vec.x = static_cast<float>(a);
	_vec.y = 0.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_newy(double a)
{
	float2_t _vec{};
	_vec.x = 0.0f;
	_vec.y = static_cast<float>(a);
	return _vec._rep;
}

GMVEC2_API double vec2_newa(double a)
{
	float2_t _vec{};
	_vec.y = _vec.x = static_cast<float>(a);
	return _vec._rep;
}

GMVEC2_API double vec2_zero()
{
	return 0;
}

GMVEC2_API double vec2_one()
{
	float2_t _vec{};
	_vec.y = _vec.x = 1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_negone()
{
	float2_t _vec{};
	_vec.y = _vec.x =-1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_unitx()
{
	float2_t _vec{};
	_vec.x = 1.0f;
	_vec.y = 0.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_unity()
{
	float2_t _vec{};
	_vec.x = 0.0f;
	_vec.y = 1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_min(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = fminf(_lhs.x, _rhs.x);
	_lhs.x = fminf(_lhs.y, _rhs.y);
	return _lhs._rep;
}

GMVEC2_API double vec2_max(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = fmaxf(_lhs.x, _rhs.x);
	_lhs.x = fmaxf(_lhs.y, _rhs.y);
	return _lhs._rep;
}

GMVEC2_API double vec2_mean(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = (_lhs.x + _rhs.x) * 0.5f;
	_lhs.x = (_lhs.y + _rhs.y) * 0.5f;
	return _lhs._rep;
}

GMVEC2_API double vec2_addmul(double lhs, double rhs, double vec)
{
	float2_t _lhs{ lhs }, _rhs{ rhs }, _vec{vec};
	_lhs.x += _rhs.x; _lhs.x *= _vec.x;
	_lhs.y += _rhs.y; _lhs.y *= _vec.y;
	return _lhs._rep;
}
GMVEC2_API double vec2_addmula(double lhs, double rhs, double a)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	float _a = static_cast<float>(a);
	_lhs.x += _rhs.x; _lhs.x *= _a;
	_lhs.y += _rhs.y; _lhs.y *= _a;
	return _lhs._rep;
}

GMVEC2_API double vec2_submul(double lhs, double rhs, double vec)
{
	float2_t _lhs{ lhs }, _rhs{ rhs }, _vec{ vec };
	_lhs.x -= _rhs.x; _lhs.x *= _vec.x;
	_lhs.y -= _rhs.y; _lhs.y *= _vec.y;
	return _lhs._rep;
}
GMVEC2_API double vec2_submula(double lhs, double rhs, double a)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	float _a = static_cast<float>(a);
	_lhs.x -= _rhs.x; _lhs.x *= _a;
	_lhs.y -= _rhs.y; _lhs.y *= _a;
	return _lhs._rep;
}

GMVEC2_API double vec2_add(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x += _rhs.x;
	_lhs.y += _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_sub(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x -= _rhs.x;
	_lhs.y -= _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_mul(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x *= _rhs.x;
	_lhs.y *= _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_div(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x /= _rhs.x;
	_lhs.y /= _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_mod(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = fmodf(_lhs.x, _rhs.x);
	_lhs.y = fmodf(_lhs.y, _rhs.y);
	return _lhs._rep;
}

GMVEC2_API double vec2_adda(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = static_cast<float>(a);
	_lhs.x += _a;
	_lhs.y += _a;
	return _lhs._rep;
}

GMVEC2_API double vec2_suba(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = static_cast<float>(a);
	_lhs.x -= _a;
	_lhs.y -= _a;
	return _lhs._rep;
}

GMVEC2_API double vec2_mula(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = static_cast<float>(a);
	_lhs.x *= _a;
	_lhs.y *= _a;
	return _lhs._rep;
}

GMVEC2_API double vec2_diva(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = static_cast<float>(a);
	_lhs.x /= _a;
	_lhs.y /= _a;
	return _lhs._rep;
}

GMVEC2_API double vec2_moda(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = static_cast<float>(a);
	_lhs.x = fmod(_lhs.x, _a);
	_lhs.y = fmod(_lhs.y, _a);
	return _lhs._rep;
}

GMVEC2_API double vec2_asub(double a, double vec)
{
	float2_t _rhs{ vec };
	float _a = static_cast<float>(a);
	_rhs.x = _a - _rhs.x;
	_rhs.y = _a - _rhs.y;
	return _rhs._rep;
}

GMVEC2_API double vec2_adiv(double a, double vec)
{
	float2_t _rhs{ vec };
	float _a = static_cast<float>(a);
	_rhs.x = _a / _rhs.x;
	_rhs.y = _a / _rhs.y;
	return _rhs._rep;
}

GMVEC2_API double vec2_amod(double a, double vec)
{
	float2_t _rhs{ vec };
	float _a = static_cast<float>(a);
	_rhs.x = fmod(_a, _rhs.x);
	_rhs.y = fmod(_a, _rhs.y);
	return _rhs._rep;
}

GMVEC2_API double vec2_dot(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	return static_cast<double>(_lhs.x * _rhs.x + _lhs.y * _rhs.y);
}

GMVEC2_API double vec2_cross(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	return static_cast<double>(_lhs.x * _rhs.y - _lhs.y * _rhs.x);
}

GMVEC2_API double vec2_normalize(double vec)
{
	float2_t _vec{ vec };
	float _alpha = 1.0f / std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
	_vec.x = _vec.x * _alpha;
	_vec.y = _vec.y * _alpha;
	return _vec._rep;
}

GMVEC2_API double vec2_length(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y));
}

GMVEC2_API double vec2_length2(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(_vec.x * _vec.x + _vec.y * _vec.y);
}

GMVEC2_API double vec2_sum(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(_vec.x + _vec.y);
}

GMVEC2_API double vec2_prod(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(_vec.x * _vec.y);
}

GMVEC2_API double vec2_dres(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(_vec.x / _vec.y);
}

GMVEC2_API double vec2_hypot(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(hypot(_vec.x, _vec.y));
}

GMVEC2_API double vec2_sign(double vec)
{
	float2_t _vec{ vec };
	_vec.x = _vec.x >= 0 ? 1.0f : -1.0f;
	_vec.y = _vec.y >= 0 ? 1.0f : -1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_sign0(double vec)
{
	float2_t _vec{ vec };
	float bx = float(_vec.x != 0);
	float by = float(_vec.y != 0);
	_vec.x = (_vec.x >= 0 ? 1.0f : -1.0f) * bx;
	_vec.y = (_vec.y >= 0 ? 1.0f : -1.0f) * by;
	return _vec._rep;
}

GMVEC2_API double vec2_clamp(double vec, double min, double max)
{
	float2_t _vec{ vec };
	float _min = static_cast<float>(min);
	float _max = static_cast<float>(max);
	_vec.x = fminf(fmaxf(_vec.x, _min), _max);
	_vec.y = fminf(fmaxf(_vec.y, _min), _max);
	return _vec._rep;
}

GMVEC2_API double vec2_clamp2(double vec, double vmin, double vmax)
{
	float2_t _vec{ vec }, _min{ vmin }, _max{ vmax };
	_vec.x = fminf(fmaxf(_vec.x, _min.x), _max.x);
	_vec.y = fminf(fmaxf(_vec.y, _min.y), _max.y);
	return _vec._rep;
}

GMVEC2_API double vec2_purge(double vec, double min, double max)
{
	float2_t _vec{ vec };
	float _min = static_cast<float>(min);
	float _max = static_cast<float>(max);
	if (_vec.x >= _min && _vec.x <= _max) { _vec.x = (_vec.x - _min) < (_max - _vec.x) ? _min : _max; }
	if (_vec.y >= _min && _vec.y <= _max) { _vec.y = (_vec.y - _min) < (_max - _vec.y) ? _min : _max; }
	return _vec._rep;
}

GMVEC2_API double vec2_purge2(double vec, double vmin, double vmax)
{
	float2_t _vec{ vec }, _min{ vmin }, _max{ vmax };
	if (_vec.x >= _min.x && _vec.x <= _max.x) { _vec.x = (_vec.x - _min.x) < (_max.x - _vec.x) ? _min.x : _max.x; }
	if (_vec.y >= _min.x && _vec.y <= _max.x) { _vec.y = (_vec.y - _max.x) < (_max.x - _vec.y) ? _min.x : _max.x; }
	return _vec._rep;
}

GMVEC2_API double vec2_step(double vec, double step)
{
	float2_t _vec{ vec };
	float _step = static_cast<float>(step);
	_vec.x = _vec.x < _step ? 0.0f : 1.0f;
	_vec.y = _vec.y < _step ? 0.0f : 1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_step2(double vec, double vstep)
{
	float2_t _vec{ vec }, _step{ vstep };
	_vec.x = _vec.x < _step.x ? 0.0f : 1.0f;
	_vec.y = _vec.y < _step.y ? 0.0f : 1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_qstep(double vec, double step)
{
	float2_t _vec{ vec };
	float _step = static_cast<float>(step);
	_vec.x = float(int(_vec.x / _step)) * _step;
	_vec.y = float(int(_vec.y / _step)) * _step;
	return _vec._rep;
}

GMVEC2_API double vec2_qstep2(double vec, double vstep)
{
	float2_t _vec{ vec }, _step{ vstep };
	_vec.x = float(int(_vec.x / _step.x)) * _step.x;
	_vec.y = float(int(_vec.y / _step.y)) * _step.y;
	return _vec._rep;
}

GMVEC2_API double vec2_rstep(double vec, double step)
{
	float2_t _vec{ vec };
	float _step = static_cast<float>(step);
	_vec.x = roundf(fmodf(_vec.x, _step) / _step);
	_vec.x = roundf(fmodf(_vec.y, _step) / _step);
	return _vec._rep;
}

GMVEC2_API double vec2_rstep2(double vec, double vstep)
{
	float2_t _vec{ vec }, _step{ vstep };
	_vec.x = roundf(fmodf(_vec.x, _step.x) / _step.x);
	_vec.x = roundf(fmodf(_vec.y, _step.y) / _step.y);
	return _vec._rep;
}

GMVEC2_API double vec2_rqstep(double vec, double step)
{
	float2_t _vec{ vec };
	float _step = static_cast<float>(step);
	_vec.x = roundf(_vec.x / _step) * _step;
	_vec.x = roundf(_vec.y / _step) * _step;
	return _vec._rep;
}

GMVEC2_API double vec2_rqstep2(double vec, double vstep)
{
	float2_t _vec{ vec }, _step{ vstep };
	_vec.x = roundf(_vec.x / _step.x) * _step.x;
	_vec.x = roundf(_vec.y / _step.y) * _step.y;
	return _vec._rep;
}

GMVEC2_API double vec2_eq(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x == _rhs.x;
	_lhs.y = _lhs.y == _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_lt(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x < _rhs.x;
	_lhs.y = _lhs.y < _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_gt(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x > _rhs.x;
	_lhs.y = _lhs.y > _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_ltq(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x <= _rhs.x;
	_lhs.y = _lhs.y <= _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_gtq(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x >= _rhs.x;
	_lhs.y = _lhs.y >= _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_neq(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x != _rhs.x;
	_lhs.y = _lhs.y != _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_and(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x && _rhs.x;
	_lhs.y = _lhs.y && _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_or(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = _lhs.x || _rhs.x;
	_lhs.y = _lhs.y || _rhs.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_not(double vec)
{
	float2_t _vec{ vec };
	_vec.x = !_vec.x;
	_vec.y = !_vec.y;
	return _vec._rep;
}

GMVEC2_API double vec2_vm1(double vec)
{
	float2_t _vec{ vec };
	_vec.x -= 1.0f;
	_vec.y -= 1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_v1m(double vec)
{
	float2_t _vec{ vec };
	_vec.x = 1.0f - _vec.x;
	_vec.y = 1.0f - _vec.y;
	return _vec._rep;
}

GMVEC2_API double vec2_vp1(double vec)
{
	float2_t _vec{ vec };
	_vec.x += 1.0f;
	_vec.y += 1.0f;
	return _vec._rep;
}

GMVEC2_API double vec2_v1p(double vec)
{
	float2_t _vec{ vec };
	_vec.x = 1.0f + _vec.x;
	_vec.y = 1.0f + _vec.y;
	return _vec._rep;
}


GMVEC2_API double vec2_floor(double vec)
{
	float2_t _vec{ vec };
	_vec.x = floorf(_vec.x);
	_vec.y = floorf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_ceil(double vec)
{
	float2_t _vec{ vec };
	_vec.x = ceilf(_vec.x);
	_vec.y = ceilf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_round(double vec)
{
	float2_t _vec{ vec };
	_vec.x = roundf(_vec.x);
	_vec.y = roundf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_cos(double vec)
{
	float2_t _vec{ vec };
	_vec.x = cosf(_vec.x);
	_vec.y = cosf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_sin(double vec)
{
	float2_t _vec{ vec };
	_vec.x = sinf(_vec.x);
	_vec.y = sinf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_tan(double vec)
{
	float2_t _vec{ vec };
	_vec.x = tanf(_vec.x);
	_vec.y = tanf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_acos(double vec)
{
	float2_t _vec{ vec };
	_vec.x = acosf(_vec.x);
	_vec.y = acosf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_asin(double vec)
{
	float2_t _vec{ vec };
	_vec.x = asinf(_vec.x);
	_vec.y = asinf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_atan(double vec)
{
	float2_t _vec{ vec };
	_vec.x = atanf(_vec.x);
	_vec.y = atanf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_cosh(double vec)
{
	float2_t _vec{ vec };
	_vec.x = coshf(_vec.x);
	_vec.y = coshf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_sinh(double vec)
{
	float2_t _vec{ vec };
	_vec.x = sinhf(_vec.x);
	_vec.y = sinhf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_tanh(double vec)
{
	float2_t _vec{ vec };
	_vec.x = tanhf(_vec.x);
	_vec.y = tanhf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_acosh(double vec)
{
	float2_t _vec{ vec };
	_vec.x = acoshf(_vec.x);
	_vec.y = acoshf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_asinh(double vec)
{
	float2_t _vec{ vec };
	_vec.x = asinhf(_vec.x);
	_vec.y = asinhf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_atanh(double vec)
{
	float2_t _vec{ vec };
	_vec.x = atanhf(_vec.x);
	_vec.y = atanhf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_act(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	return static_cast<double>(_lhs.x * _rhs.y + _lhs.y * _rhs.y);
}

GMVEC2_API double vec2_rotate(double vec, double theta)
{
	float2_t _vec{ vec };
	float _theta = static_cast<float>(theta);
	float _cos = cosf(_theta);
	float _sin = sinf(_theta);
	_vec.x = _vec.x * _cos - _vec.y * _sin;
	_vec.y = _vec.x * _sin + _vec.y * _cos;
	return _vec._rep;
}

GMVEC2_API double vec2_scale(double vec, double alpha)
{
	float2_t _vec{ vec };
	float _alpha = static_cast<float>(alpha);
	_vec.x *= _alpha;
	_vec.y *= _alpha;
	return _vec._rep;
}

GMVEC2_API double vec2_rotate2(double vec, double origin, double theta)
{
	float2_t _vec{ vec }, _origin{ origin };
	float _theta = static_cast<float>(theta);
	float _cos = cosf(_theta);
	float _sin = sinf(_theta);
	_vec.x = _vec.x - _origin.x;
	_vec.y = _vec.y - _origin.y;
	_vec.x = _vec.x * _cos - _vec.y * _sin + _origin.x;
	_vec.y = _vec.x * _sin + _vec.y * _cos + _origin.y;
	return _vec._rep;
}

GMVEC2_API double vec2_scale2(double vec, double origin, double alpha)
{
	float2_t _vec{ vec }, _origin{ origin };
	float _alpha = static_cast<float>(alpha);
	_vec.x = _vec.x - _origin.x;
	_vec.y = _vec.y - _origin.y;
	_vec.x *= _alpha;
	_vec.y *= _alpha;
	return _vec._rep;
}

GMVEC2_API double vec2_lerp(double lhs, double rhs, double alpha)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	float _alpha = static_cast<float>(alpha);
	_lhs.x = _lhs.x + (_rhs.x - _lhs.x) * _alpha;
	_lhs.y = _lhs.y + (_rhs.y - _lhs.y) * _alpha;
	return _lhs._rep;
}

GMVEC2_API double vec2_lerp2(double lhs, double rhs, double valpha)
{
	float2_t _lhs{ lhs }, _rhs{ rhs }, _alpha{ valpha };
	_lhs.x = _lhs.x + (_rhs.x - _lhs.x) * _alpha.x;
	_lhs.y = _lhs.y + (_rhs.y - _lhs.y) * _alpha.y;
	return _lhs._rep;
}

GMVEC2_API double vec2_interp(double vec, double tar, double dt, double omega)
{
	float2_t _vec{ vec }, _dist{ tar };
	float _dt = static_cast<float>(dt);
	float _omega = static_cast<float>(omega);
	if (_omega <= 0.0) { return tar; }
	_dist.x -= _vec.x;
	_dist.y -= _vec.y;
	float _len2 = _dist.x * _dist.x + _dist.y * _dist.y;
	if (_len2 < _VEC2_EPS_1) { return tar; }
	_dist.x *= fminf(fmaxf(_dt * _omega, 0.0f), 1.0f);
	_dist.y *= fminf(fmaxf(_dt * _omega, 0.0f), 1.0f);
	_vec.x += _dist.x;
	_vec.y += _dist.y;
	return _vec._rep;
}

GMVEC2_API double vec2_interp2(double vec, double tar, double dt, double vomega)
{
	float2_t _vec{ vec }, _dist{ tar }, _omega{ vomega };
	float _dt = static_cast<float>(dt);
	if (_omega.x * _omega.y <= 0.0) { return tar; }
	_dist.x -= _vec.x;
	_dist.y -= _vec.y;
	float _len2 = _dist.x * _dist.x + _dist.y * _dist.y;
	if (_len2 < _VEC2_EPS_1) { return tar; }
	_dist.x *= fminf(fmaxf(_dt * _omega.x, 0.0f), 1.0f);
	_dist.y *= fminf(fmaxf(_dt * _omega.y, 0.0f), 1.0f);
	_vec.x += _dist.x;
	_vec.y += _dist.y;
	return _vec._rep;
}

GMVEC2_API double vec2_smoothd(double vec, double tar, char* ptr_vel, double dt, double max, double omega)
{
	float2_t _vec{ vec }, _tar{ tar }, _vel{ *reinterpret_cast<double*>(ptr_vel) }, _dist{ tar },
		_temp{}, _old{ tar }, _out{};

	float _dt = static_cast<float>(dt);
	float _omega = fmaxf(_VEC2_EPS_1, static_cast<float>(omega));
	
	float _exp = _omega * _dt;
	_exp = 1.0f / (1.0f + _exp + 0.48f * _exp * _exp + 0.235f * _exp * _exp * _exp);
	
	_dist.x -= _vec.x;
	_dist.y -= _vec.y;

	float _max = _omega * static_cast<float>(max);
	_dist.x = fminf(fmaxf(_dist.x, -_max), _max);
	_dist.y = fminf(fmaxf(_dist.y, -_max), _max);
	_tar.x = _vec.x - _dist.x;
	_tar.y = _vec.y - _dist.y;
	
	_temp.x = (_vel.x + _omega * _dist.x) * _dt;
	_temp.y = (_vel.y + _omega * _dist.y) * _dt;
	_vel.x = (_vel.x - _omega * _temp.x) * _exp;
	_vel.y = (_vel.y - _omega * _temp.y) * _exp;
	_out.x = _tar.x + (_dist.x + _temp.x) * _exp;
	_out.y = _tar.y + (_dist.y + _temp.y) * _exp;

	bool bcorr = (_old.x - _vec.x > _VEC2_EPS_1) == (_out.x > _old.x)
		&& (_old.y - _vec.y > _VEC2_EPS_1) == (_out.y > _old.y);

	if (bcorr)
	{
		_out.x = _old.x;
		_out.y = _old.y;
		_vel.x = (_out.x - _old.x) / _dt;
		_vel.y = (_out.y - _old.y) / _dt;
	}

	return _out._rep;
}

GMVEC2_API double vec2_smoothd2(double vec, double tar, char* ptr_vel, double dt, double vmax, double vomega)
{
	float2_t _vec{ vec }, _tar{ tar }, _vel{ *reinterpret_cast<double*>(ptr_vel) }, _dist{tar}, _omega{vomega}, _max{vmax},
		_temp{}, _old{ tar }, _out{}, _exp{ dt };

	float _dt = static_cast<float>(dt);
	_omega.x = fmaxf(_VEC2_EPS_1, static_cast<float>(_omega.x));
	_omega.y = fmaxf(_VEC2_EPS_1, static_cast<float>(_omega.y));

	_exp.x *= _omega.x;
	_exp.y *= _omega.y;
	_exp.x = 1.0f / (1.0f + _exp.x + 0.48f * _exp.x * _exp.x + 0.235f * _exp.x * _exp.x * _exp.x);
	_exp.y = 1.0f / (1.0f + _exp.y + 0.48f * _exp.y * _exp.y + 0.235f * _exp.y * _exp.y * _exp.y);

	_dist.x -= _vec.x;
	_dist.y -= _vec.y;

	_max.x = _omega.x * _max.x;
	_max.y = _omega.y * _max.y;
	_dist.x = fminf(fmaxf(_dist.x, -_max.x), _max.x);
	_dist.y = fminf(fmaxf(_dist.y, -_max.y), _max.y);
	_tar.x = _vec.x - _dist.x;
	_tar.y = _vec.y - _dist.y;

	_temp.x = (_vel.x + _omega.x * _dist.x) * _dt;
	_temp.y = (_vel.y + _omega.y * _dist.y) * _dt;
	_vel.x = (_vel.x - _omega.x * _temp.x) * _exp.x;
	_vel.y = (_vel.y - _omega.y * _temp.y) * _exp.y;
	_out.x = _tar.x + (_dist.x + _temp.x) * _exp.x;
	_out.y = _tar.y + (_dist.y + _temp.y) * _exp.y;

	bool bcorr = (_old.x - _vec.x > _VEC2_EPS_1) == (_out.x > _old.x)
		&& (_old.y - _vec.y > _VEC2_EPS_1) == (_out.y > _old.y);

	if (bcorr)
	{
		_out.x = _old.x;
		_out.y = _old.y;
		_vel.x = (_out.x - _old.x) / _dt;
		_vel.y = (_out.y - _old.y) / _dt;
	}

	return _out._rep;
}

GMVEC2_API double vec2_mine(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(_vec.x < _vec.y ? _vec.x : _vec.y);
}

GMVEC2_API double vec2_maxe(double vec)
{
	float2_t _vec{ vec };
	return static_cast<double>(_vec.x > _vec.y ? _vec.x : _vec.y);
}

GMVEC2_API double vec2_signe(double vec)
{
	float2_t _vec{ vec };
	return (_vec.x >= 0) && (_vec.y >= 0) ? 1.0 : -1.0;
}

GMVEC2_API double vec2_sign0e(double vec)
{
	float2_t _vec{ vec };
	return ((_vec.x >= 0) && (_vec.y >= 0) ? 1.0 : -1.0) * double(_vec.x != 0 || _vec.y != 0);
}

GMVEC2_API double vec2_sqrt(double vec)
{
	float2_t _vec{ vec };
	_vec.x = sqrtf(_vec.x);
	_vec.y = sqrtf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_sq(double vec)
{
	float2_t _vec{ vec };
	_vec.x *= _vec.x;
	_vec.y *= _vec.y;
	return _vec._rep;
}

GMVEC2_API double vec2_ln(double vec)
{
	float2_t _vec{ vec };
	_vec.x = logf(_vec.x);
	_vec.y = logf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_ln1p(double vec)
{
	float2_t _vec{ vec };
	_vec.x = log1pf(_vec.x);
	_vec.y = log1pf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_log10(double vec)
{
	float2_t _vec{ vec };
	_vec.x = log10f(_vec.x);
	_vec.y = log10f(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_log2(double vec)
{
	float2_t _vec{ vec };
	_vec.x = log2f(_vec.x);
	_vec.y = log2f(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_exp(double vec)
{
	float2_t _vec{ vec };
	_vec.x = expf(_vec.x);
	_vec.y = expf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_exp2(double vec)
{
	float2_t _vec{ vec };
	_vec.x = exp2f(_vec.x);
	_vec.y = exp2f(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_expm1(double vec)
{
	float2_t _vec{ vec };
	_vec.x = expm1f(_vec.x);
	_vec.y = expm1f(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_pow(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = powf(_lhs.x, _rhs.x);
	_lhs.y = powf(_lhs.y, _rhs.y);
	return _lhs._rep;
}

GMVEC2_API double vec2_rt(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = powf(_lhs.x, -_rhs.x);
	_lhs.y = powf(_lhs.y, -_rhs.y);
	return _lhs._rep;
}

GMVEC2_API double vec2_log(double lhs, double rhs)
{
	float2_t _lhs{ lhs }, _rhs{ rhs };
	_lhs.x = logf(_lhs.x) / logf(_rhs.x);
	_lhs.y = logf(_lhs.y) / logf(_rhs.y);
	return _lhs._rep;
}

GMVEC2_API double vec2_powa(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = static_cast<float>(a);
	_lhs.x = powf(_lhs.x, _a);
	_lhs.y = powf(_lhs.y, _a);
	return _lhs._rep;
}

GMVEC2_API double vec2_rta(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = -static_cast<float>(a);
	_lhs.x = powf(_lhs.x, _a);
	_lhs.y = powf(_lhs.y, _a);
	return _lhs._rep;
}

GMVEC2_API double vec2_loga(double vec, double a)
{
	float2_t _lhs{ vec };
	float _a = logf(static_cast<float>(a));
	_lhs.x = logf(_lhs.x) / _a;
	_lhs.y = logf(_lhs.y) / _a;
	return _lhs._rep;
}

GMVEC2_API double vec2_apow(double a, double vec)
{
	float2_t _rhs{ vec };
	float _a = static_cast<float>(a);
	_rhs.x = powf(_a, _rhs.x);
	_rhs.y = powf(_a, _rhs.y);
	return _rhs._rep;
}
GMVEC2_API double vec2_art(double a, double vec)
{
	float2_t _rhs{ vec };
	float _a = static_cast<float>(a);
	_rhs.x = powf(_a, -_rhs.x);
	_rhs.y = powf(_a, -_rhs.y);
	return _rhs._rep;
}
GMVEC2_API double vec2_alog(double a, double vec)
{
	float2_t _rhs{ vec };
	float _a = static_cast<float>(a);
	_rhs.x = _a / logf(_rhs.x);
	_rhs.y = _a / logf(_rhs.y);
	return _rhs._rep;
}

GMVEC2_API double vec2_erf(double vec)
{
	float2_t _vec{ vec };
	_vec.x = erff(_vec.x);
	_vec.y = erff(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_erfc(double vec)
{
	float2_t _vec{ vec };
	_vec.x = erfcf(_vec.x);
	_vec.y = erfcf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_tgamma(double vec)
{
	float2_t _vec{ vec };
	_vec.x = tgammaf(_vec.x);
	_vec.y = tgammaf(_vec.y);
	return _vec._rep;
}

GMVEC2_API double vec2_lgamma(double vec)
{
	float2_t _vec{ vec };
	_vec.x = lgammaf(_vec.x);
	_vec.y = lgammaf(_vec.y);
	return _vec._rep;
}
