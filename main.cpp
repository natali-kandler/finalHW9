#include <iostream>
#include <cstring>
#include <stdio.h>
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"
#include "string.h"

int main(int argc, char **argv) {

  int args_fine = check_args(argc, argv);
  if (args_fine != 0) {
    return -1;
  }

  String *law_arr;
  size_t size_of_law_arr;
  String *pattern_arr;
  size_t pat_arr_size;
  String law_base_string;
  bool is_law_valid = false;
  law_base_string = argv[1];
  Field *field_ptr_check = nullptr;
  law_base_string.split("=", &law_arr, &size_of_law_arr);
  law_arr[0].split("-", &pattern_arr, &pat_arr_size);
  if ((pattern_arr[1].trim()).equals("ip")) {
    Ip ip_law(law_arr[0].trim());
    String trimmed_law_arr = law_arr[1].trim();
    is_law_valid = ip_law.set_value(trimmed_law_arr);
    if (!is_law_valid) {
      delete[] pattern_arr;
      delete[] law_arr;
      return -1;
    }
    field_ptr_check = &ip_law;
    parse_input(*field_ptr_check);
  } else if ((pattern_arr[1].trim()).equals("port")) {
    Port port_law(law_arr[0].trim());
    is_law_valid = port_law.set_value(law_arr[1].trim());
    if (!is_law_valid) {
      delete[] pattern_arr;
      delete[] law_arr;
      return -1;
    }
    field_ptr_check = &port_law;
    parse_input(*field_ptr_check);
  }

  delete[] pattern_arr;
  delete[] law_arr;

  return 0;

}
