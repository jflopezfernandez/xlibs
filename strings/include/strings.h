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

#ifndef PROJECT_INCLUDES_XLIBS_STRINGS_H
#define PROJECT_INCLUDES_XLIBS_STRINGS_H

/**
 * String searching algorithms recognized by the library.
 *
 * @enum string_search_algorithm_t
 *
 */
typedef enum {
    NAIVE_STRING_SEARCH,
    RABIN_KARP_STRING_SEARCH,
    FINITE_AUTOMATON_STRING_SEARCH,
    KNUTH_MORRIS_PRATT_STRING_SEARCH
} string_search_algorithm_t;

/*
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
const char*
__attribute__((nonnull(2,3)))
find_substring(string_search_algorithm_t algorithm, const char* needle, const char* haystack);

/**
 * Valid Metric Distance Metrics
 *
 * This enum defines the valid edit distance calculation
 * algorithms accepted by the calculate_edit_distance()
 * function.
 *
 * @typedef edit_distance_t
 *
 */
typedef enum {
    LEVENSHTEIN_DISTANCE,
    LONGEST_COMMON_SUBSEQUENCE,
    HAMMING_DISTANCE,
    DAMERAU_LEVENSHTEIN_DISTANCE,
    JARO_DISTANCE
} edit_distance_type_t;

/*
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
size_t calculate_edit_distance(edit_distance_type_t edit_distance_type, const char* a, const char* b);

/*
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
size_t
__attribute__((nonnull(1)))
string_length(const char* string);

#endif /** PROJECT_INCLUDES_XLIBS_STRINGS_H */
