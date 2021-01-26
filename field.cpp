#include <iostream>
#include <cstring>

#include "field.h"
#include "ip.h"
#include "port.h"

#include "string.h"

Field::Field(String pattern, field_type type) {
  this->type = type;
  this->pattern = pattern;
}

Field::Field(String pattern) {
  this->type = GENERIC;
  this->pattern = pattern;
}

Field::~Field() {
  // empty
}

field_type Field::get_type() const {
  return type;
}

bool Field::set_value(String val) {
  field_type our_type = get_type();
  bool is_success;
  if (our_type == IP) {
    Ip *ip = (Ip*)this;
    is_success = ip->set_value(val);
  } else if (our_type == PORT) {
    Port *port = (Port*)this;
    is_success = port->set_value(val);
  } else {
    is_success = false;
  }
  return is_success;
}

bool Field::match_value(String val) const {
  field_type our_type = get_type();
  bool is_success;
  if (our_type == IP) {
    Ip *ip = (Ip*)this;
    is_success = ip->match_value(val);
  } else if (our_type == PORT) {
    Port *port = (Port*)this;
    is_success = port->match_value(val);
  } else {
    is_success = false;
  }
 
  return is_success;
}

bool Field::match(String packet) {
  String *packet_parts;
  size_t size_of_arr;
  packet.split(",=", &packet_parts, &size_of_arr);
  bool is_equal = false;
  bool are_matching =false;
  for (size_t i = 0; i < (size_of_arr/2); ++i) {
    is_equal = pattern.equals(packet_parts[2*i].trim());
    if (is_equal) {
      are_matching = match_value(packet_parts[2 * i + 1].trim());
    }
  }
  delete[] packet_parts;
  return are_matching;
}
