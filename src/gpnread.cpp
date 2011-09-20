/**
 * @file main.cpp main definitions
 * @author Roland Hieber <rohieb@rohieb.name>
 * @date 2011-08-04
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

#include "gpnread.h"
#include <fstream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <map>

using namespace std;

namespace gpnread {

/**
 * Constructor, optionally opens the .gpn file to read from.
 * @param filename Name of the file to read from. The file must be readable to
 *  the user. If empty, no file will be opened.
 * @throws std::ifstream::failure in case the file could not be opened
 */
GpnRead::GpnRead(const char * filename = "") : in(new ifstream) {
  in->exceptions(ifstream::failbit | ifstream::badbit);
  if(strlen(filename) > 0) {
    open(filename);
  }
}

// Stuff for the callback function map for record types
// First, some convenience typedefs
namespace {
  /** An alphabetic string comparator */
  struct ltstr {
    bool operator()(const string s1, const string s2) const {
      return s1.compare(s2) < 0;
    }
  };
  /** Type of a record type */
  typedef const string rectype_t;
  /** Type of a function for record types */
  typedef boost::function<void (string&, string&)> rectype_cb_t;
  /** Type of the function map to map record types to functions */
  typedef std::map<rectype_t, rectype_cb_t, ltstr> rectype_cb_map_t;
} // namespace

/**
 * Open a file.
 * @param filename Name of the file to read from. The file must be readable to
 *  the user. If empty, no file will be opened.
 * @throws std::ifstream::failure in case the file could not be opened
 * @todo write about Parser Hooks
 */
void GpnRead::open(const char * filename) {
  // Build the callback function map for record types
  // TODO: Add handlers for new record types here!

  /** The actual map for mapping record types fo functions */
  rectype_cb_map_t cbMap;
  cbMap["00"] = boost::bind(&MasterData::parseBasic, &master_data, _1, _2);

  // other initialization
  in->open(filename, ios_base::in);
  while(!in->eof()) {
    // process each line
    string line;
    getline(*in, line);

    // get record type and text
    string recType = line.substr(0,2);
    string text = line.substr(2);
    cout << "Read rectype " << recType << ", content " << text << endl;
    // and call function
    if(cbMap.count(recType) == 1) {
      cbMap[recType](recType, text);
    } else {
      cerr << "Error: function for record type `" << recType <<
        "' not yet implemented!" << endl;
    }
  }
}

} // namespace gpnread
