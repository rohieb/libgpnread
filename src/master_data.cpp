/**
 * @file master_data.cpp Implementation for reading Master Data
 * @date 2011-04-08
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

#include "master_data.h"
#include <string>
#include <sstream>
using namespace std;
using namespace gpnread;

/**
 * Parser hook for Master Data records (record type @c 00)
 */
void MasterData::parseBasic(string& rectype, string& text) {
  uint32_t bgColor, fgColor;
  NameRecord * nmr = new NameRecord;

  // first fill the basic data

//  vector<string> varData;
//  boost::algorithm::split(varData, text.substr(5), boost::algorithm::);

  switch(text.at(0)) {
    case 'K': nmr = new Class; break;
    case 'L': nmr = new Teacher; break;
    case 'R': nmr = new Room; break;
    case 'F': nmr = new Subject; break;
    case 'M': nmr = new Department; break;
    case '=': nmr = new Description; break;
  }


}
