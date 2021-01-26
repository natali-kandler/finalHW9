#include <iostream>
#include <cstring>

#include "field.h"
#include "ip.h"

enum { MIN32B = 0, MAX32B = 4294967295 };

Ip::Ip(String pattern) : Field(pattern, IP) {
  low = MIN32B;
  high = MAX32B;
}

bool Ip::set_value(String val) {
  String *val_parts;
  size_t size_of_arr;
  val.split("./", &val_parts, &size_of_arr);
  const int size_of_law = 5;
  bool is_law_fine = true;

  if (size_of_arr != size_of_law) {
    is_law_fine = false;
  } else {
    int mask = (val_parts[SEGMENTS].trim()).to_integer();
    if ((mask > 32) || (mask < 0)) {
      is_law_fine = false;
    } else {
      int mask_comp = (32 - mask);
      unsigned int ip_num = 0;
      int val_int;
      for (int i = 0; (i < SEGMENTS) && is_law_fine; ++i) {
        val_int = (val_parts[i].trim()).to_integer();
        if ((val_int > 255) || (val_int < 0)) {
          is_law_fine = false;
        } else {
          ip_num += (val_int << (24 - (8 * i)));
        }
      }
      if (is_law_fine && (mask != 0)) {
        low = (ip_num >> mask_comp);
        low = (low << mask_comp);
        unsigned int high_ones = ((unsigned) MAX32B >> (unsigned) mask);
        if (mask != 32) {
          high = low + high_ones;
        } else {
          high = low;
        }
      }
    }
  }
  delete[] val_parts;
  return is_law_fine;
}

bool Ip::match_value(String val) const {
  String *val_parts;
  size_t size_of_arr;
  const int expect_arr_size = 4;
  val.split(".", &val_parts, &size_of_arr);
  if (size_of_arr != expect_arr_size) {
    delete[] val_parts;
    return false;
  }
  unsigned int ip_num = 0;
  int val_int;
  bool is_lawful = false;
  for (int i = 0; i < SEGMENTS; ++i) {
    val_int = (val_parts[i].trim()).to_integer();
    if ((val_int < 0) || (val_int > 255)) {
      delete[] val_parts;
      return false;
    }
    ip_num += (val_int << (24 - (8 * i)));
  }
  if ((ip_num >= low) && (ip_num <= high)) {
    is_lawful = true;
  }
  delete[] val_parts;
  return is_lawful;
}
