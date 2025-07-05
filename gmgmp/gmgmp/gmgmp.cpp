// gmgmp.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "gmgmp.h"

#include <cstdlib>
#include <climits>
#pragma warning(push)
#pragma warning(disable:4146)
#include <gmp/gmp.h>
#pragma warning(pop)

GMGMP_API int _fn_gmgmp()
{
	return 42;
}

GMGMP_API int _fn_gmgmp_arg(int arg)
{
	return arg;
}


char* returnstring = NULL;

inline char* _fix_try_nullstr(char* _smem)
{
	_smem = (char*)(malloc(1));
	if (_smem != NULL) { _smem[0] = '\0'; }
	return _smem;
}

inline char* _fix_try_0x0str(char* _smem)
{
	_smem = (char*)malloc(4);
	if (_smem != NULL) { strcpy_s(_smem, 4, "0x0"); }
	else { _smem = _fix_try_nullstr(_smem); }
	return _smem;
}

inline int gm_cast_int(double d) {
	if ((double)(int)(INT_MIN) <= d && d <= (double)(int)(INT_MAX)) return (int)(d);
	else return 0;
}

void make_returnstring_dec(mpz_t a) {
	free(returnstring);
	returnstring = (char*)(malloc(mpz_sizeinbase(a, 10) + 2));
	if (returnstring == NULL) { _fix_try_nullstr(returnstring); }
	else { mpz_get_str(returnstring, 10, a); }
}
void make_returnstring_hex(mpz_t a) {
	free(returnstring);
	returnstring = (char*)(malloc(mpz_sizeinbase(a, 16) + 4));
	if (returnstring == NULL) { _fix_try_nullstr(returnstring); }
	else
	{
		mpz_get_str(returnstring + 2, 16, a);
		if (returnstring[2] == '-') {
			returnstring[0] = '-';
			returnstring[1] = '0';
			returnstring[2] = 'x';
		}
		else {
			returnstring[0] = '0';
			returnstring[1] = 'x';
		}
	}
}

GMGMP_API double gmp_real(char* a_string)
{
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	double result = mpz_get_d(a);
	mpz_clear(a);
	return result;
}

GMGMP_API char* gmp_string(double a_real) {
	mpz_t a;
	mpz_init_set_d(a, a_real);
	make_returnstring_hex(a);
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_tohex(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	make_returnstring_hex(a);
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_todec(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	make_returnstring_dec(a);
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_add(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	mpz_add(a, a, b);
	make_returnstring_hex(a);
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_sub(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	mpz_sub(a, a, b);
	make_returnstring_hex(a);
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_mul(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	mpz_mul(a, a, b);
	make_returnstring_hex(a);
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_div(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	if (mpz_sgn(b) == 0) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_tdiv_q(a, a, b);
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_mod(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	if (mpz_sgn(b) == 0) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_tdiv_r(a, a, b);
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_neg(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	mpz_neg(a, a);
	make_returnstring_hex(a);
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_abs(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	mpz_abs(a, a);
	make_returnstring_hex(a);
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_pow(char* base_string, char* n_string) {
	mpz_t a, b;
	mpz_init_set_str(a, base_string, 0);
	mpz_init_set_str(b, n_string, 0);
	if (!mpz_fits_ulong_p(b)) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_pow_ui(a, a, mpz_get_ui(b));
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_powmod(char* base_string, char* n_string, char* mod_string) {
	mpz_t a, b, c;
	mpz_init_set_str(a, base_string, 0);
	mpz_init_set_str(b, n_string, 0);
	mpz_init_set_str(c, mod_string, 0);
	if (mpz_sgn(c) < 0) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_powm(a, a, b, c);
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	return returnstring;
}

GMGMP_API char* gmp_sqrt(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	if (mpz_sgn(a) < 0) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_sqrt(a, a);
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_sqrtrem(char* a_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init(b);
	if (mpz_sgn(a) < 0) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_sqrtrem(a, b, a);
		make_returnstring_hex(b);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_root(char* a_string, char* n_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, n_string, 0);
	if ((mpz_sgn(a) < 0 && mpz_even_p(b)) || !mpz_fits_ulong_p(b)) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_root(a, a, mpz_get_ui(b));
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_rootrem(char* a_string, char* n_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, n_string, 0);
	if ((mpz_sgn(a) < 0 && mpz_even_p(b)) || !mpz_fits_ulong_p(b)) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_rootrem(a, b, a, mpz_get_ui(b));
		make_returnstring_hex(b);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API double gmp_compare(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	int result = mpz_cmp(a, b);
	mpz_clear(a);
	mpz_clear(b);
	return result;
}

GMGMP_API double gmp_abscompare(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	int result = mpz_cmpabs(a, b);
	mpz_clear(a);
	mpz_clear(b);
	return result;
}

GMGMP_API double gmp_sign(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	int result = mpz_sgn(a);
	mpz_clear(a);
	return result;
}

GMGMP_API double gmp_even(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	bool result = mpz_even_p(a);
	mpz_clear(a);
	return result;
}

GMGMP_API double gmp_odd(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	bool result = mpz_odd_p(a);
	mpz_clear(a);
	return result;
}

GMGMP_API double gmp_probab_prime(char* a_string, double reps) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	int result = mpz_probab_prime_p(a, gm_cast_int(reps));
	mpz_clear(a);
	return result;
}

GMGMP_API char* gmp_probab_nextprime(char* a_string) {
	mpz_t a;
	mpz_init_set_str(a, a_string, 0);
	mpz_nextprime(a, a);
	make_returnstring_hex(a);
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_gcd(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	mpz_gcd(a, a, b);
	make_returnstring_hex(a);
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_lcm(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	mpz_lcm(a, a, b);
	make_returnstring_hex(a);
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_factorial(char* n_string) {
	mpz_t a;
	mpz_init_set_str(a, n_string, 0);
	if (!mpz_fits_ulong_p(a)) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_fac_ui(a, mpz_get_ui(a));
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_fibonacci(char* n_string) {
	mpz_t a;
	mpz_init_set_str(a, n_string, 0);
	if (!mpz_fits_ulong_p(a)) {
		free(returnstring);
		_fix_try_0x0str(returnstring);
	}
	else {
		mpz_fib_ui(a, mpz_get_ui(a));
		make_returnstring_hex(a);
	}
	mpz_clear(a);
	return returnstring;
}

GMGMP_API char* gmp_min(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	if (mpz_cmp(a, b) < 0) {
		make_returnstring_hex(a);
	}
	else {
		make_returnstring_hex(b);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}

GMGMP_API char* gmp_max(char* a_string, char* b_string) {
	mpz_t a, b;
	mpz_init_set_str(a, a_string, 0);
	mpz_init_set_str(b, b_string, 0);
	if (mpz_cmp(a, b) > 0) {
		make_returnstring_hex(a);
	}
	else {
		make_returnstring_hex(b);
	}
	mpz_clear(a);
	mpz_clear(b);
	return returnstring;
}