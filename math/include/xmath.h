/*
 * xlibs - C Programming Language Extensions Libraries
 * Copyright (C) 2020 Jose Fernando Lopez Fernandez
 * 
 * This program is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <https://www.gnu.org/licenses/>.
 *
 */

#ifndef PROJECT_INCLUDES_XMATH_H
#define PROJECT_INCLUDES_XMATH_H

// #ifndef PROJECT_INCLUDES_LIBCX_TYPES_H
// #include "types.h"
// #endif

typedef enum {
    false = 0,
    true  = 1
} bool_t;

/**
 * This macro definition is required for Doxygen to be able
 * to parse the function declaration correctly.
 *
 * @def __attribute_const
 *
 */
#ifndef __attribute_const
#define __attribute_const __attribute__((const))
#endif

/*
 * Absolute Value
 *
 * This function returns the absolute value of the input,
 * except for the case where the input is zero, in which
 * case the result is again zero.
 *
 * @param[in] x The number to evalue the absolute value of.
 *
 * @returns The absolute value of the integer x.
 *
 * @todo Write man page for this function.
 *
 */
int __attribute_const abs(int x);

/*
 * Greatest Common Divisor
 *
 * This function computes the greatest common divisor of two
 * integers using a simple implementation of the Euclidean
 * algorithm that does not rely on division operations. I
 * have not performed a comparative profile of this method
 * versus one using division operations, but my hunch is
 * that this method is faster. As I said, however, this
 * hunch is based on zero actual information.
 *
 * @param[in] a First factor
 * @param[in] b Second factor
 *
 * @returns The greatest common divisor of a and b.
 *
 * @note In order for this simpler subtraction-based
 * algorithm to work, both numbers must be greater than zero
 * (obviously), as otherwise the algorithm would never
 * terminate.
 *
 * @todo Write man page for this function.
 *
 */
int __attribute_const gcd(int a, int b);

/*
 * Least Common Multiple
 *
 * This function returns the least common multiple of the
 * integers a and b by leveraging the Greatest Common
 * Denominator function defined within this same module.
 *
 * @param[in] a First factor.
 * @param[in] b Second factor.
 *
 * @returns The smallest integer divisible by both a and b.
 *
 * @remark The requirement that both a and b be non-negative
 * integers applies in this function just as it does in the
 * gcd() function, since it is implicitly used in the final
 * calculation.
 *
 * @todo Write man page for this function.
 *
 */
int __attribute_const lcm(int a, int b);

/*
 * Is Prime
 *
 * This function checks whether a given number is prime by
 * brute-force, attempting to divide the given number \f$n\f$ by
 * every number \f$n-1\f$.
 *
 * @param[in] n The number to test for primality.
 *
 * @returns A boolean value which is true if \f$n\f$ is prime.
 *
 * @note As is customary in mathematics, \f$1\f$ is
 * considered prime.
 *
 * @todo Write man page for this function.
 *
 */
bool_t __attribute_const is_prime(int n);

/*
 * Modular Exponentiation
 *
 * This function uses the binary representation of \f$b\f$
 * to efficiently perform exponentiation. The method relies
 * on repeated squaring, as described by Cormen, et. al., in
 * <I>Introduction to Algorithms</I>. The result of this
 * function is equal to the following equation.
 * \f[d = a^b \text{mod }d\f]
 *
 *
 * @param[in] a Number to raise to a power.
 * @param[in] b The power to raise \f$a\f$ to.
 * @param[in] d The modulus to reduce \f$a^b\f$ by.
 *
 * @returns The result of the above equation.
 *
 * @cite cormen_introduction_2009
 *
 */
int
__attribute__((pure))
modular_exponentiation(int a, int b, int n);

int least_common_multiple(void);

#endif /** PROJECT_INCLUDES_XMATH_H */
