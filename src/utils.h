/**
 * @file utils Declaration of useful helper functions
 * @date 2011-08-18
 * @author Roland Hieber <rohieb@rohieb.name>
 *
 * Copyright (c) 2011 Roland Hieber
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <set>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

namespace gpnread {

/**
 * Determine the unique characters occuring in a string.
 * @param s The string
 * @return The set of characters which are present in the given string
 */
std::set<char> charset(std::string s);

/**
 * Get the variable fields from a text string. The fields have to be
 * comma-separated. If a field should contain one or more literal commas, the
 * contents of the field have to start and end in a quotation mark (@c ") which
 * are omitted in the parsed field and not written to the output.
 *
 * @param container Vector to hold the contents of the fields. If the
 *  conversion was successful, this vector contains the value of the @i n-th
 *  field in its @i n-th element.
 *
 * @param text String of comma-separated fields to be parsed.
 *
 * return @c false if there was an uneven number of quotation marks in the
 *  string, or @c true otherwise. In the first case, the container array may
 *  contain unwanted results.
 */
bool getVarFields(std::vector<std::string>& container, std::string text);

} // namespace gpnread

#endif /* UTILS_H_ */
