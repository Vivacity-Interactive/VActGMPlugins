#pragma once

#ifndef GMGMP_API
#define GMGMP_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

GMGMP_API double _fn_gmgmp(void);
GMGMP_API double _fn_gmgmp_arg(double arg);

GMGMP_API double gmp_real(char* a_string);
GMGMP_API char* gmp_string(double a_real);
GMGMP_API char* gmp_tohex(char* a_string);
GMGMP_API char* gmp_todec(char* a_string);
GMGMP_API char* gmp_add(char* a_string, char* b_string);
GMGMP_API char* gmp_sub(char* a_string, char* b_string);
GMGMP_API char* gmp_mul(char* a_string, char* b_string);
GMGMP_API char* gmp_div(char* a_string, char* b_string);
GMGMP_API char* gmp_mod(char* a_string, char* b_string);
GMGMP_API char* gmp_neg(char* a_string);
GMGMP_API char* gmp_abs(char* a_string);
GMGMP_API char* gmp_pow(char* base_string, char* n_string);
GMGMP_API char* gmp_powmod(char* base_string, char* n_string, char* mod_string);
GMGMP_API char* gmp_sqrt(char* a_string);
GMGMP_API char* gmp_sqrtrem(char* a_string);
GMGMP_API char* gmp_root(char* a_string, char* n_string);
GMGMP_API char* gmp_rootrem(char* a_string, char* n_string);
GMGMP_API double gmp_compare(char* a_string, char* b_string);
GMGMP_API double gmp_abscompare(char* a_string, char* b_string);
GMGMP_API double gmp_sign(char* a_string);
GMGMP_API double gmp_even(char* a_string);
GMGMP_API double gmp_odd(char* a_string);
GMGMP_API double gmp_probab_prime(char* a_string, double reps);
GMGMP_API char* gmp_probab_nextprime(char* a_string);
GMGMP_API char* gmp_gcd(char* a_string, char* b_string);
GMGMP_API char* gmp_lcm(char* a_string, char* b_string);
GMGMP_API char* gmp_factorial(char* n_string);
GMGMP_API char* gmp_fibonacci(char* n_string);
GMGMP_API char* gmp_min(char* a_string, char* b_string);
GMGMP_API char* gmp_max(char* a_string, char* b_string);

#ifdef __cplusplus
}
#endif