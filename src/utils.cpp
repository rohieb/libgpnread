/**
 * @file utils.cpp Definition of useful helper functions
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

#include "utils.h"
#include <sstream>

using namespace std;

namespace gpnread {

/*
 * get set of chars occuring in string
 */
set<char> charset(string s) {
  set<char> chars;
  for(string::iterator it = s.begin(); it != s.end(); it++) {
    chars.insert(*it);
  }
  return chars;
}

/*
 * split string at comma, but ignore commas between quotation marks
 */
bool getVarFields(vector<string>& container, string text) {
  stringstream ss(text);
  string field;
  char c;
  bool quotation = false;

  container.clear();

  // note: fields end at newline
  while(ss.good() && ss.get(c) && c != '\n' && c != '\r') {
    if(c == '"') {
      quotation = !quotation;

    } else if(c == ',') {
      if(quotation) {
        field.push_back(',');
      } else {
        container.push_back(field);
        field.clear();
      }

    } else {
      field.push_back(c);
    }
  }
  container.push_back(field); // at EOL or error

  return !quotation;
}

} // namespace gpnread
