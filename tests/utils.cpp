/**
 * @file utils.cpp Unit tests for the file src/utils.cpp
 * @date 07.09.2011
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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE utils
#include <src/utils.h>
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace gpnread;

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(charsetTest) {
  set<char> v = charset(string(""));
  char r[] = { 'a', 's' };
  BOOST_CHECK_EQUAL(v.size(), 0);

  v = charset(string("sa"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r, r + 2);

  v = charset(string("asa"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r, r + 2);

  v = charset(string("aas"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r, r + 2);

  v = charset(string("saas"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r, r + 2);

  v = charset(string("saasasass"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r, r + 2);
}

////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(getVarFieldsTest) {
  vector<string> v;
  string r1[] = { "as", "df", "safa" };
  BOOST_REQUIRE(getVarFields(v, "as,df,safa"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r1, r1 + 3);

  string r2[] = { "Foo,Bar,foobar", "baz", "quux" };
  BOOST_REQUIRE(getVarFields(v, "\"Foo,Bar,foobar\",baz,quux"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r2, r2 + 3);

  string r3[] = { "Foo", "Bar", "baz" };
  BOOST_REQUIRE(getVarFields(v, "\"Foo\",Bar,baz"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r3, r3 + 3);

  string r4[] = { "Foo", "Bar", "baz" };
  BOOST_REQUIRE(getVarFields(v, "Foo,\"Bar\",baz"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r4, r4 + 3);

  string r5[] = { "Foo", "Bar,baz", "baz" };
  BOOST_REQUIRE(getVarFields(v, "Foo,\"Bar,baz\",baz"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r5, r5 + 3);

  string r6[] = { "Foo", "Bar", "baz,quux" };
  BOOST_REQUIRE(getVarFields(v, "Foo,Bar,\"baz,quux\""));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r6, r6 + 3);

  // a faulty one
  string r7[] = { "Foo", "Bar", "baz,quux,quuux" };
  BOOST_REQUIRE(!getVarFields(v, "Foo,Bar,\"baz,quux,quuux"));
  BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), r7, r7 + 3);
}
