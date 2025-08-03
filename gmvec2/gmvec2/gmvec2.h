#pragma once

#ifndef GMVEC2_API
#define GMVEC2_API
#endif

#include <type_traits>
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>

#ifndef _VEC2_BUFFER_DELTA
#define _VEC2_BUFFER_DELTA 16
#endif

template<typename T0, typename T1>
struct rep_type_trait { using type = T1; };

template<typename T0>
struct rep_type_trait<T0, void> { using type = T0[2]; };

template<typename T0 = float, typename T1 = double>
struct vec2_t
{
	static_assert(sizeof(T1) == sizeof(T0) * 2, "T1 type must span entire struct");

	using rep_t = typename rep_type_trait<T0, T1>::type;

	union {
		rep_t _rep;
		struct { T0 x, y; };
		T0 vec[2];
		unsigned char _raw[sizeof(T0) * 2];
		char _buf[sizeof(T0) * 2];
	};

	inline size_t size() const { return 2; }
};

template<typename T0>
struct buffer_t
{
	size_t _size, _size_buffer;
	union
	{
		T0* _data;
		void* _ptr;
		unsigned char _raw;
		char* _buf;
	};

	buffer_t() : _data(nullptr), _size(0), _size_buffer(0) {};
	~buffer_t() { if (_data) { free(_data); _data = nullptr; _size = _size_buffer = 0; } }

	bool resize(size_t size_buffer)
	{
		void* _mem = _data ? realloc(_data, size_buffer) : malloc(size_buffer);
		if (_mem) { _data = (T0*)_mem; _size_buffer = size_buffer; }
		return !!_mem;
	}

	bool push(const T0& item)
	{
		bool bvalid = true;
		if (_size >= _size_buffer) { bvalid = resize(((_size + _VEC2_BUFFER_DELTA - 1) / _VEC2_BUFFER_DELTA) * _size); }
		if (bvalid) { _data[_size++] = item; }
		return bvalid;
	}

	inline T0 pop() { return _data[_size--]; }
	inline void clear(size_t to_size = 0) { _size = to_size; }
	inline T0* get(size_t index) { return _data + index; }
	inline const T0* get(size_t index) const { return _data + index; }
	
	inline size_t size() const { return _size; }
	inline size_t size_buffer() const { return _size_buffer; }

	inline T0* data() { return begin(); }
	inline const T0* data() const { return begin(); }
	inline T0* begin() { return _data; }
	inline T0* end() { return _data[_size]; }
	inline T0& operator[](size_t index) { return _data[index]; }
	inline const T0& operator[](size_t index) const { return _data[index]; }
};

using float2_t = vec2_t<float, double>;
using floats2_t = buffer_t<float2_t>;

extern template struct vec2_t<float, double>;
extern template struct buffer_t<vec2_t<float, double>>;

#ifdef __cplusplus
extern "C" {
#endif

	GMVEC2_API double _fn_gmvec2(void);
	GMVEC2_API double _fn_gmvec2_arg(double arg);
	GMVEC2_API void _fn_gmvec2_into(double& into);

	GMVEC2_API void vec2_init_seed(double seed);

	GMVEC2_API void vec2_buffer_free(char* ptr_buffer);
	GMVEC2_API char* vec2_buffer(double capacity);
	
	GMVEC2_API double vec2_buffer_count(char* ptr_buffer);
	GMVEC2_API double vec2_buffer_capacity(char* ptr_buffer);
	GMVEC2_API void vec2_buffer_clear(char* ptr_buffer);
	GMVEC2_API void vec2_buffer_clear2(char* ptr_buffer, double count);
	
	GMVEC2_API void vec2_buffer_push(char* ptr_buffer, double vec);
	GMVEC2_API double vec2_buffer_pop(char* ptr_buffer);
	GMVEC2_API void vec2_buffer_pop2(char* ptr_buffer, char* ptr_vec);
	
	GMVEC2_API char* vec2_buffer_get(double index, char* ptr_buffer);
	GMVEC2_API void vec2_buffer_set(double index, char* ptr_buffer, double vec);
	
	GMVEC2_API double vec2_buffer_at(double index, char* ptr_buffer);
	GMVEC2_API void vec2_buffer_at2(double index, char* ptr_buffer, char* ptr_vec);

	GMVEC2_API void vec2_free(char* ptr_vec);
	GMVEC2_API char* vec2_ptr(double vec);
	GMVEC2_API char* vec2_ptr2(double x, double y);
	
	GMVEC2_API void vec2_into(char* ptr_vec, double vec);
	GMVEC2_API void vec2_into2(char* ptr_vec, double x, double y);
	
	GMVEC2_API double vec2_swap(char* ptr_lhs, char* ptr_rhs);
	GMVEC2_API double vec2_vec(char* ptr_vec);

	GMVEC2_API double vec2_rnd(double seed);
	GMVEC2_API double vec2_rndr(double min, double max, double seed);
	GMVEC2_API double vec2_rndu(double seed);
	GMVEC2_API double vec2_rndur(double min, double max, double seed);
	GMVEC2_API double vec2_rndswap(double vec, double seed);
	
	GMVEC2_API double vec2_x(double vec);
	GMVEC2_API double vec2_y(double vec);

	GMVEC2_API double vec2_new(double x, double y);
	GMVEC2_API double vec2_newx(double a);
	GMVEC2_API double vec2_newy(double a);
	GMVEC2_API double vec2_newa(double a);
	
	GMVEC2_API double vec2_zero();
	GMVEC2_API double vec2_one();
	GMVEC2_API double vec2_negone();
	GMVEC2_API double vec2_unitx();
	GMVEC2_API double vec2_unity();

	GMVEC2_API double vec2_min(double lhs, double rhs);
	GMVEC2_API double vec2_max(double lhs, double rhs);
	GMVEC2_API double vec2_mean(double lhs, double rhs);

	GMVEC2_API double vec2_addmul(double lhs, double rhs, double vec);
	GMVEC2_API double vec2_addmula(double lhs, double rhs, double a);
	GMVEC2_API double vec2_submul(double lhs, double rhs, double vec);
	GMVEC2_API double vec2_submula(double lhs, double rhs, double a);

	GMVEC2_API double vec2_add(double lhs, double rhs);
	GMVEC2_API double vec2_sub(double lhs, double rhs);
	GMVEC2_API double vec2_mul(double lhs, double rhs);
	GMVEC2_API double vec2_div(double lhs, double rhs);
	GMVEC2_API double vec2_mod(double lhs, double rhs);

	GMVEC2_API double vec2_adda(double vec, double a);
	GMVEC2_API double vec2_suba(double vec, double a);
	GMVEC2_API double vec2_mula(double vec, double a);
	GMVEC2_API double vec2_diva(double vec, double a);
	GMVEC2_API double vec2_moda(double vec, double a);

	GMVEC2_API double vec2_asub(double a, double vec);
	GMVEC2_API double vec2_adiv(double a, double vec);
	GMVEC2_API double vec2_amod(double a, double vec);

	GMVEC2_API double vec2_dot(double lhs, double rhs);
	GMVEC2_API double vec2_cross(double lhs, double rhs);

	GMVEC2_API double vec2_normalize(double vec);
	GMVEC2_API double vec2_length(double vec);
	GMVEC2_API double vec2_length2(double vec);
	GMVEC2_API double vec2_sum(double vec);
	GMVEC2_API double vec2_prod(double vec);
	GMVEC2_API double vec2_dres(double vec);
	GMVEC2_API double vec2_hypot(double vec);
	
	GMVEC2_API double vec2_sign(double vec);
	GMVEC2_API double vec2_sign0(double vec);

	GMVEC2_API double vec2_clamp(double vec, double min, double max);
	GMVEC2_API double vec2_clamp2(double vec, double vmin, double vmax);
	GMVEC2_API double vec2_purge(double vec, double min, double max);
	GMVEC2_API double vec2_purge2(double vec, double vmin, double vmax);
	GMVEC2_API double vec2_step(double vec, double step);
	GMVEC2_API double vec2_step2(double vec, double vstep);
	GMVEC2_API double vec2_qstep(double vec, double step);
	GMVEC2_API double vec2_qstep2(double vec, double vstep);
	GMVEC2_API double vec2_rstep(double vec, double step);
	GMVEC2_API double vec2_rstep2(double vec, double vstep);
	GMVEC2_API double vec2_rqstep(double vec, double step);
	GMVEC2_API double vec2_rqstep2(double vec, double vstep);

	GMVEC2_API double vec2_eq(double lhs, double rhs);
	GMVEC2_API double vec2_lt(double lhs, double rhs);
	GMVEC2_API double vec2_gt(double lhs, double rhs);
	GMVEC2_API double vec2_ltq(double lhs, double rhs);
	GMVEC2_API double vec2_gtq(double lhs, double rhs);
	GMVEC2_API double vec2_neq(double lhs, double rhs);
	GMVEC2_API double vec2_and(double lhs, double rhs);
	GMVEC2_API double vec2_or(double lhs, double rhs);
	GMVEC2_API double vec2_not(double vec);

	GMVEC2_API double vec2_vm1(double vec);
	GMVEC2_API double vec2_v1m(double vec);
	GMVEC2_API double vec2_vp1(double vec);
	GMVEC2_API double vec2_v1p(double vec);

	GMVEC2_API double vec2_floor(double vec);
	GMVEC2_API double vec2_ceil(double vec);
	GMVEC2_API double vec2_round(double vec);

	GMVEC2_API double vec2_cos(double vec);
	GMVEC2_API double vec2_sin(double vec);
	GMVEC2_API double vec2_tan(double vec);
	GMVEC2_API double vec2_acos(double vec);
	GMVEC2_API double vec2_asin(double vec);
	GMVEC2_API double vec2_atan(double vec);

	GMVEC2_API double vec2_cosh(double vec);
	GMVEC2_API double vec2_sinh(double vec);
	GMVEC2_API double vec2_tanh(double vec);
	GMVEC2_API double vec2_acosh(double vec);
	GMVEC2_API double vec2_asinh(double vec);
	GMVEC2_API double vec2_atanh(double vec);

	GMVEC2_API double vec2_act(double lhs, double rhs);
	GMVEC2_API double vec2_rotate(double vec, double theta);
	GMVEC2_API double vec2_scale(double vec, double alpha);
	GMVEC2_API double vec2_rotate2(double vec, double origin, double theta);
	GMVEC2_API double vec2_scale2(double vec, double origin, double alpha);

	GMVEC2_API double vec2_lerp(double lhs, double rhs, double alpha);
	GMVEC2_API double vec2_lerp2(double lhs, double rhs, double valpha);

	GMVEC2_API double vec2_interp(double vec, double tar, double dt, double omega);
	GMVEC2_API double vec2_interp2(double vec, double tar, double dt, double vomega);

	GMVEC2_API double vec2_smoothd(double vec, double tar, char* ptr_vel, double dt, double max, double omega);
	GMVEC2_API double vec2_smoothd2(double vec, double tar, char* ptr_vel, double dt, double max, double vomega);

	GMVEC2_API double vec2_mine(double vec);
	GMVEC2_API double vec2_maxe(double vec);
	GMVEC2_API double vec2_signe(double vec);

	GMVEC2_API double vec2_sqrt(double vec);
	GMVEC2_API double vec2_sq(double vec);
	GMVEC2_API double vec2_ln(double vec);
	GMVEC2_API double vec2_ln1p(double vec);
	GMVEC2_API double vec2_log10(double vec);
	GMVEC2_API double vec2_log2(double vec);

	GMVEC2_API double vec2_exp(double vec);
	GMVEC2_API double vec2_exp2(double vec);
	GMVEC2_API double vec2_expm1(double vec);

	GMVEC2_API double vec2_pow(double lhs, double rhs);
	GMVEC2_API double vec2_rt(double lhs, double rhs);
	GMVEC2_API double vec2_log(double lhs, double rhs);

	GMVEC2_API double vec2_powa(double vec, double a);
	GMVEC2_API double vec2_rta(double vec, double a);
	GMVEC2_API double vec2_loga(double vec, double a);

	GMVEC2_API double vec2_apow(double a, double vec);
	GMVEC2_API double vec2_art(double a, double vec);
	GMVEC2_API double vec2_alog(double a, double vec);

	GMVEC2_API double vec2_erf(double vec);
	GMVEC2_API double vec2_erfc(double vec);
	GMVEC2_API double vec2_tgamma(double vec);
	GMVEC2_API double vec2_lgamma(double vec);

#ifdef __cplusplus
}
#endif	