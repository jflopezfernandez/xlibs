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
#include <stdlib.h>
#include <string.h>

#ifndef XLIBS_INTERNAL
#define XLIBS_INTERNAL
#endif

#include "strings.h"

/**
 * Calculate the length of the given string.
 *
 * The function returns the length of the string pointed to
 * by <U>string</U>, excluding the null terminator.
 *
 * @param[in] string Pointer to null-terminated string.
 *
 * @returns Length of the given string, minus null terminator.
 *
 */
size_t string_length(const char* string) {
    size_t length = 0;

    while ((string[length] != '\0'))
        ++length;
    
    return length;
}
