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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef XLIBS_INTERNAL
#define XLIBS_INTERNAL
#endif

#include "strings.h"

/**
 * Naive String Search Algorithm
 *
 * This algorithm is a naive implementation of a string
 * searching algorithm. As noted in <I>Introduction to
 * Algorithms</I>, by Cormen, et. al., this algorithm has a
 * runtime complexity of \f$O\left(\left(n-m+1\right)m\right)\f$.
 *
 * @param[in] needle The substring to search for.
 * @param[in] haystack The string to look for the substring in.
 *
 * @returns Pointer to the start of the substring within the
 * haystack. If the needle is not found in the haystack, the
 * returned pointer will be equal to NULL.
 *
 * @cite cormen_introduction_2009
 *
 */
static const char* naive_string_search(const char* needle, const char* haystack) {
    size_t n = strlen(needle);
    size_t h = strlen(haystack);

    for (size_t i = 0; i < h - n; ++i) {
        if (needle[0] == haystack[0 + i]) {
            for (size_t j = 1; j < n; ++j) {
                if (needle[j] != haystack[j + i]) {
                    break;
                }

                if (j == (n -1)) {
                    return haystack + i;
                }
            }
        }
    }
    
    return NULL;
}

static const char* rabin_karp_string_search(const char* needle, const char* haystack) {
    return NULL;
}

static const char* finite_automaton_string_search(const char* needle, const char* haystack) {
    return NULL;
}

/**
 * Knuth-Morris-Pratt String Search Prefix Preprocessing
 *
 * This function allocates and initializes the auxiliary
 * array required by the Knuth-Morris-Pratt string search
 * algorithm.
 *
 * @param[in] needle The substring to search for.
 *
 * @returns The array of pre-computed shifts required by the
 * Knuth-Morris-Pratt algorithm.
 *
 * @cite cormen_introduction_2009
 *
 */
static size_t* knuth_morris_pratt_compute_prefix_function(const char* needle) {
    size_t m = strlen(needle);

    size_t* p = malloc(sizeof (size_t) * (m + 1));

    if (p == NULL) {
        fprintf(stderr, "[Error] %s\n", "Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    memset(p, 0, sizeof (size_t) * (m + 1));

    p[0] = 0;
    
    size_t k = 0;

    for (size_t q = 1; q < m; ++q) {
        while ((k > 0) && (needle[k] != needle[q])) {
            k = p[k];
        }

        if (needle[k] == needle[q]) {
            k = k + 1;
        }

        p[q] = k;
    }

    return p;
}

/**
 * Knuth-Morris-Pratt String Search
 *
 * This function searches the haystack text buffer for the
 * substring specified by the needle argument using the
 * Knuth-Morris-Pratt algorithm as described in the 3rd
 * Edition of <I>Introduction to Algorithms</I> by Cormen,
 * et al.
 *
 * @param[in] needle The substring to search for.
 * @param[in] haystack The text to look for the substring in.
 *
 * @returns Pointer to the start of the substring within the
 * haystack. If the needle is not found in the haystack, the
 * returned pointer will be equal to NULL.
 *
 * @cite cormen_introduction_2009
 *
 */
static const char* knuth_morris_pratt_string_search(const char* needle, const char* haystack) {
    size_t m = strlen(needle);
    size_t n = strlen(haystack);
    size_t*p = knuth_morris_pratt_compute_prefix_function(needle);
    size_t q = 0;

    for (size_t i = 0; i < n; ++i) {
        while ((q > 0) && (needle[q] != haystack[i])) {
            q = p[q];
        }

        if (needle[q] == haystack[i]) {
            q = q + 1;
        }

        if (q == m) {
            free(p);
            return haystack + i - m + 1;
        }
    }

    return NULL;
}

/**
 * String Search Function
 *
 * This type alias allows us to return a function pointer
 * from the get_string_search_function(), making the string
 * searching API much more convenient, and the codebase much
 * easier to maintain.
 *
 * @typedef string_search_function_t
 *
 */
typedef const char* (*string_search_function_t)(const char*, const char*);

/**
 * Get String Search Function
 *
 * This function takes the argument specified by the user in
 * the call to find_substring(), and it returns a function
 * pointer to the correct string searching function.
 *
 * @param[in] algorithm The desired string searching algorithm.
 *
 * @returns Function pointer to the appropriate string
 * searching function.
 *
 */
string_search_function_t get_string_search_function(string_search_algorithm_t algorithm) {
    switch (algorithm) {
        case NAIVE_STRING_SEARCH: return naive_string_search;
        case RABIN_KARP_STRING_SEARCH: return rabin_karp_string_search;
        case FINITE_AUTOMATON_STRING_SEARCH: return finite_automaton_string_search;
        case KNUTH_MORRIS_PRATT_STRING_SEARCH: return knuth_morris_pratt_string_search;
    }
    
    /**
     * Since the passed-in value was not recognized, use the
     * default string searching algorithm.
     *
     * @todo Allow for the configuration of a default
     * algorithm during library configuration.
     *
     */
    return knuth_morris_pratt_string_search;
}

/**
 * Find a string within a string.
 *
 * This function searches the haystack for an instance of
 * the needle.
 *
 * @param[in] algorithm The algorithm to use for the search.
 * @param[in] needle    The substring to look for.
 * @param[in] haystack  The string to look in.
 *
 * @returns Pointer to the located string. If the substring
 * is not found, the returned pointer is equal to NULL.
 *
 */
const char* find_substring(string_search_algorithm_t algorithm, const char* needle, const char* haystack) {
    return get_string_search_function(algorithm)(needle, haystack);
}
