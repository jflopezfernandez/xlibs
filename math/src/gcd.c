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

#include <stddef.h>
#include <stdint.h>

#include "xmath.h"

/**
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
 * @param[in] a First factor.
 * @param[in] b Second factor.
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
int gcd(int a, int b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }

    return a;
}
