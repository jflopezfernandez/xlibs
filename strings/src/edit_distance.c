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

#ifndef MAX
#define MAX(a,b) ((a < b) ? (b) : (a))
#endif

#ifndef MIN
#define MIN(a,b) ((a > b) ? (b) : (a))
#endif

static size_t min3(size_t a, size_t b, size_t c) {
    size_t minimum = MIN(a,b);
    return MIN(minimum,c);
}

/**
 * Calculate the Levenshtein distance between the strings
 * represented by a and b.
 *
 * The current implementation uses the Fischer-Wagner
 * algorithm to calculate the Levenshtein distance between
 * the two strings.
 *
 * @param[in] a The first string to compare.
 * @param[in] b The second string to compare.
 *
 * @returns The edit distance between a and b , as defined
 * by the Levenshtein distance between them.
 *
 * @todo Implement this function.
 * @todo Write the man page for this function.
 * @todo Implement a more efficient version of this
 * algorithm. The current version has a time and memory
 * complexity of O(n*m).
 *
 */
static size_t
__attribute__((nonnull(1,2)))
calculate_levenshtein_distance(const char* a, const char* b) {
    size_t m = strlen(a) + 1;
    size_t n = strlen(b) + 1;

    /**
     * For all \f$i\f$ and \f$j\f$, the value \f$\text{distance}\left[i\right]\left[j\right]\f$
     * will hold the Levenshtein distance between the first
     * \f$i\f$ characters of a and the first \f$j\f$
     * characters of b.
     *
     */
    size_t d[m][n];// = { 0 };
    
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            d[i][j] = 0;
        }
    }

    /**
     * Source prefixes can be transformed into the empty
     * string by dropping all characters.
     *
     */
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (j == 0) {
                d[i][j] = i;
            }
        }
    }

    /**
     * Target prefixes can be reached from an empty source
     * prefix by inserting each character in succession.
     *
     */
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i == 0) {
                d[i][j] = j;
            }
        }
    }

    for (size_t i = 1; i < m; ++i) {
        for (size_t j = 1; j < n; ++j) {
            size_t substitution_cost = ((a[i-1] == b[j-1]) ? 0 : 1);
            d[i][j] = min3(d[i-1][j] + 1, d[i][j-1] + 1, d[i-1][j-1] + substitution_cost);
        }
    }

    // for (size_t i = 0; i < m; ++i) {
    //     for (size_t j = 0; j < n; ++j) {
    //         printf("%lu ", d[i][j]);
    //     }

    //     printf("\n");
    // }

    // printf("\n");

    return d[m-1][n-1];
}

/**
 * Calculate the longest common subsequence between the
 * strings represented by a and b.
 *
 * @param[in] a The first string to compare.
 * @param[in] b The second string to compare.
 *
 * @returns The edit distance between a and b , as defined
 * by the length of the longest common subsequence between
 * them.
 *
 * @todo Implement this function.
 * @todo Write the man page for this function.
 *
 */
static size_t calculate_longest_common_subsequence_distance(const char* a, const char* b) {
    /**
     * Return the maximum unsigned long integer as a 
     * non-sensical value to represent the function not
     * having been implemented yet.
     *
     */
    return (size_t) -1;
}

static size_t calculate_hamming_distance(const char* a, const char* b) {
    /**
     * Return the maximum unsigned long integer as a 
     * non-sensical value to represent the function not
     * having been implemented yet.
     *
     */
    return (size_t) -1;
}

static size_t calculate_damerau_levenshtein_distance(const char* a, const char* b) {
    /**
     * Return the maximum unsigned long integer as a 
     * non-sensical value to represent the function not
     * having been implemented yet.
     *
     */
    return (size_t) -1;
}

static size_t calculate_jaro_distance(const char* a, const char* b) {
    /**
     * Return the maximum unsigned long integer as a 
     * non-sensical value to represent the function not
     * having been implemented yet.
     *
     */
    return (size_t) -1;
}

/**
 * Edit Distance Calculation Function Pointer
 *
 * This typedef conveniently allows for the selection of a
 * particular edit distance calculation algorithm at runtime
 * by the user.
 *
 * @typedef edit_distance_function_t
 *
 */
typedef size_t (*edit_distance_function_t)(const char*, const char*);

/**
 * Get Edit Distance Function
 *
 * This function takes a single parameter, in which the user
 * specifies the desired edit distance calculation algorithm
 * by passing in the appropriate value, as specified by the
 * edit_distance_type_t enumeration.
 *
 * @param[in] edit_distance_type Desired edit distance algorithm.
 *
 * @returns Function pointer to the requested algorithm calculation function.
 *
 */
static edit_distance_function_t get_edit_distance_function(edit_distance_type_t edit_distance_type) {
    /**
     * Initialize the edit distance function pointer to NULL
     * to represent no function being selected.
     *
     * @todo The default edit distance should probably be
     * configurable by the end-user during initial library
     * configuration.
     *
     */
    edit_distance_function_t edit_distance_function = NULL;

    switch (edit_distance_type) {
        case LEVENSHTEIN_DISTANCE: {
            edit_distance_function = calculate_levenshtein_distance;
        } break;

        case LONGEST_COMMON_SUBSEQUENCE: {
            edit_distance_function = calculate_longest_common_subsequence_distance;
        } break;

        case HAMMING_DISTANCE: {
            edit_distance_function = calculate_hamming_distance;
        } break;

        case DAMERAU_LEVENSHTEIN_DISTANCE: {
            edit_distance_function = calculate_damerau_levenshtein_distance;
        } break;

        case JARO_DISTANCE: {
            edit_distance_function = calculate_jaro_distance;
        } break;

        default: {
            /**
             * The default action here will be to let the user know
             * we were unable to recognize a valid edit distance
             * metric based on the value they specified. We then let
             * them know we will be reverting to the default, and we
             * return whatever the default function is configured to
             * be.
             *
             */
            fprintf(stderr, "[Error] %s\n", "Distance metric not recognized. Reverting to the default value.");
        } break;
    }

    /** Return the edit distance function pointer. */
    return edit_distance_function;
}

/**
 * Calculate the edit distance of two given strings.
 *
 * In addition to the two input string arguments, this
 * function takes takes a third argument, used to specify
 * the edit distance algorithm to use when calculating the
 * metric.
 *
 * @param[in] edit_distance_type    The edit distance metric to use.
 * @param[in] a                     The first string to compare.
 * @param[in] b                     The second string to compare.
 *
 * @returns The edit distance between a and b, as calculated
 * by the edit distance algorithm specified.
 *
 */
size_t calculate_edit_distance(edit_distance_type_t edit_distance_type, const char* a, const char* b) {
    return get_edit_distance_function(edit_distance_type)(a,b);
}
