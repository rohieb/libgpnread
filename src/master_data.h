/**
 * @file master_data.h -- declaration for master data in GPN files
 * @date 2011-08-04
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

#include <string>

using namespace std;

namespace gpnread {

/** Structure of a generic master data record */
struct MasterData {
  /** Type of the record */
  enum RecordType {
    RECORD_CLASS, /*< This record describes a class */
    RECORD_ROOM,  /*< This record describes a room */
    RECORD_TEACHER, /*< This record describes a teacher */
    RECORD_SUBJECT, /*< This record describes a teaching subject */
    RECORD_DEPT,    /*< This record describes a departement */
    RECORD_CORR,    /*< This record describes a corridor */
    // FIXME: what do these mean, and do we need them?
    //RECORD_LSN_GRP, /*< This record describes a lesson group */
    //RECORD_LSN_TBL, /*< This record describes a lesson table */
    //RECORD_DESCR,   /*< This record describes a description */
    //RECORD_STUDENT, /*< This record describes a student */
  };

  /** Short name of the described item */
  string shortName;
  /** Full name of the described item */
  string fullName;
  /**
   * Room name, if applicable
   * FIXME: must be pointer to room!
   */
  string roomName;
  string description;
  string value;
  string generalText;
  unsigned int fgColor;
  unsigned int bgColor;
  string key;
  // FIXME need flags!

  static void parseBasic(string& text);
};

} // namespace gpnread
