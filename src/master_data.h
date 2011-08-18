/**
 * @file master_data.h declaration for master data in GPN files
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
#include <map>
#include <set>
#include <stdint.h>
#include <boost/shared_ptr.hpp>

using namespace std;

namespace gpnread {

/**
 * A color in RGB color space
 */
struct Color {
  /** red value */
  uint8_t red;
  /** green value */
  uint8_t green;
  /** blue value */
  uint8_t blue;
  /**
   * Constructor. Initializes each color value individually.
   * @param r red value
   * @param g green value
   * @param b blue value
   */
  Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) :
    red(r), green(g), blue(b) {
  }
  /**
   * Constructor. Initializes the color values by a 32-bit value.
   * @param value A 32-bit value containing the color values as following:
   *  - blue value in the least siginificant byte,
   *  - green value in the second-least significant byte,
   *  - red value in the second-most significant byte,
   *  - the most significant byte is ignored.
   *  Example: @c 0xffc3f099 leads to a blue value of @c 0x99, a green value of
   *  @c 0xf0 and a red value of @c 0xc3.
   */
  Color(uint32_t value) :
    red((value >> 16) & 0xff), green((value >> 8) & 0xff), blue(value & 0xff) {
  }
};

struct Room; /* we only need it here for the shared ptr */

/**
 * Common fields for each Master Data record
 */
struct NameRecord {
  /** Short name of the described item */
  string shortName;
  /** Full name of the described item */
  string fullName;
  /** Room associated with the item */
  boost::shared_ptr<Room> roomName;
  /** General text for the item */
  string generalText;
  /**
   * Short description of the item
   * @todo needs to be pointer to description
   */
  string descr;
  /** not used, seems to be always empty */
  string value;
  /** Foreground color */
  Color fgColor;
  /** Background color */
  Color bgColor;
  /** not used, seems to be always empty */
  string key;
  /** not used, seems to be always empty */
  string dataFields;
  /**
   * Flags: A set of single characters with the following meaning if set:
   *  - @c A: No non-teaching periods (NTPs) (only for teachers)
   *  - @c A: Subject to all classes (only for subjects)
   *  - @c B: Respect lunch break (only for teachers)
   *  - @c C: Respect max. periods per day (only for teachers)
   *  - @c D: Respect max. consecutive periods (only for teachers)
   *  - @c D: Respect double periods (only for subjects)
   *  - @c E: Double periods are allowed to span *-breaks (only for subjects)
   *  - @c F: Lessons not on consecutive days (only for classes)
   *  - @c F: Optional subject (only for subjects)
   *  - @c G: Do not schedule in first or last lesson (only for subjects)
   *  - @c H: Schedule either AM or PM, not both (for classes, teachers)
   *  - @c H: Main subject (only for subjects)
   *  - @c I: Ignored in the timetable (for classes, teachers, subjects)
   *  - @c M: Lunch break is a non-teaching period (for classes, teachers)
   *  - @c m: Mark for printing
   *  - @c N: Do not print
   *  - @c n: male (for teachers, students; forbids @c W)
   *  - @c P: Non-teaching periods (NTPs) allowed (only for classes)
   *  - @c R: Do not schedule in the first and last period of a day (only
   *    for teachers)
   *  - @c R: Schedule in first or last period (only for subjects)
   *  - @c W: female (for teachers, students; forbids @c n)
   *  - @c X: Locked in the timetable (for classes, teachers, rooms, subjects)
   *  - @c Y: Block periods before first and after last scheduled period of
   *    half-day (for classes, teachers)
   *  - @c 2: Can be scheduled more than once a day (only for subjects)
   */
  set<char> flags;
  /**
   * Statistical codes: set of single characters. Semantical meaning is
   * determined by the end user.
   */
  set<char> statCodes;
};

/**
 * Structure describing a class
 * @todo
 */
struct Class : NameRecord {
};

/**
 * Structure describing a teacher
 * @todo
 */
struct Teacher : NameRecord {
};

/**
 * Structure describing a room
 * @todo
 */
struct Room : NameRecord {
};

/**
 * Structure describing a teaching subject
 * @todo
 */
struct Subject : NameRecord {
};

class MasterData {
public:
  void parseBasic(string& rectype, string& text);

  /** map from class short names to class records */
  map<string, boost::shared_ptr<Class> > classes;
  /** map from teacher short names to teacher records */
  map<string, boost::shared_ptr<Teacher> > teachers;
  /** map from room short names to room records */
  map<string, boost::shared_ptr<Room> > rooms;
  /** map from subject short names to subject records */
  map<string, boost::shared_ptr<Subject> > subjects;

private:
  /** pointer to the last inserted class record */
  boost::shared_ptr<Class> lastClass;
  /** pointer to the last inserted teacher record */
  boost::shared_ptr<Teacher> lastTeacher;
  /** pointer to the last inserted room record */
  boost::shared_ptr<Room> lastRoom;
  /** pointer to the last inserted subject record */
  boost::shared_ptr<Subject> lastSubject;
};

} // namespace gpnread
