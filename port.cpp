#include <iostream>
#include <cstring>

#include "field.h"

#include "port.h"



enum { MIN16B = 0, MAX16B = 65535 };

Port::Port(String pattern) : Field(pattern, PORT) {
  range[0] = MIN16B;
  range[1] = MAX16B;
}

bool Port::set_value(String val) {
  String *val_parts;
  size_t size_of_arr;
  const int law_size = 2;

  val.split("-", &val_parts, &size_of_arr);
  bool is_law_fine = true; 
  if (size_of_arr != law_size) {
    is_law_fine = false;
  } else {
    int lower_lim = ((val_parts[0]).trim()).to_integer();
    int upper_lim = ((val_parts[1]).trim()).to_integer();
    if (lower_lim > upper_lim ||
        (lower_lim < MIN16B) ||
        (upper_lim > MAX16B)) {
      is_law_fine = false;
    } else { 
      range[0] = lower_lim;
      range[1] = upper_lim;
    }
  }

  delete[] val_parts;
  return is_law_fine;
}

bool Port::match_value(String val) const {
  bool is_lawful = false;
  int val_num = val.to_integer();
  if ((val_num >= range[0]) && (val_num <= range[1])) {
    is_lawful = true;
  }
  return is_lawful;
}
