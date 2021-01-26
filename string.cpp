#include <iostream>
#include <cstring>

#include "string.h"

using namespace std;
/**
 * creates a new copy of input string, the copy is restricted by size or end
 * of string
 * @param src string to copy
 * @param len max length to copy
 * @return the new copy of the string.
 * note: the user is responsible to delete the return value
 */
static char *create_new_copy(const char *src, size_t len) {
  char *dst;
  if (src == NULL) {
    return NULL;
  }
  dst = new char[len + 1];
  for (size_t i = 0; i <= len; i++) {
    dst[i] = src[i];
  }
  dst[len] = '\0';
  return dst;
}
/**
 * the function checks if a char does exist in a given array
 * @param data the char to search in the array
 * @param array_deli the array to check
 * @return true if the char exists in the array, false otherwise
 */
bool does_exist(const char data, const char *array_deli) {
  if (array_deli == NULL) {
    return false;
  }
  int count = 0;
  while (array_deli[count] != '\0') {
    if (data == array_deli[count]) {
      return true;
    }
    count++;
  }
  return false;
}

String::String() {
  data = new char[1];
  *data = '\0';
  length = 0;
}

String::String(const String &str) {
    length = str.length;
    data = create_new_copy(str.data, str.length);
}

String::String(const char *str) {
  length = strlen(str);
  data = create_new_copy(str, length);
}

String::~String() {
  if (data != NULL) {
    delete[] data;
  }
}

String &String::operator=(const String &rhs) {
  if (this != &rhs) {
    length = rhs.length;
    delete[] data;
    data = create_new_copy(rhs.data, rhs.length);
  }
  return *this;
}

String &String::operator=(const char *str) {
  length = strlen(str);
  delete[] data;
  data = create_new_copy(str, length);
  return *this;
}

bool String::equals(const char *rhs) const {
  return !strcmp(data, rhs);
}

bool String::equals(const String &rhs) const {
  return equals(rhs.data);
}

void String::split(const char *delimiters,
                   String **output,
                   size_t *size) const {
  if (size == NULL) {
    return;
  }
  bool output_is_null = false;

  if (output ==  NULL){
  	output_is_null = true; 
  }

  if ((delimiters == NULL) || (*delimiters == '\0') || (*data == '\0')) {
    *size = 1;
    if (!output_is_null) {
      String *output_arr = new String[*size];
      String new_str(*this);
      output_arr[0] = new_str;
      *output = output_arr;
    }
    return;
  }
  size_t size_of_arr = 0;
  int begin_count = 0;
  int end_count = 0;
  bool prev_is_deli = does_exist(data[end_count], delimiters);
  bool end_of_data = false;
  if (prev_is_deli) {
    begin_count++;
  }
  end_count++;
  int *array = new int[2*length + 1];
  int a_i = 0;
  while (!end_of_data) {
    bool curr_is_deli = ((*(data + end_count) == '\0') ||
                          (does_exist(data[end_count], delimiters)));
    if (curr_is_deli) {
      if (!prev_is_deli) {
        array[a_i++] = begin_count;
        array[a_i++] = end_count;
        size_of_arr++;
      }
      begin_count = end_count + 1;
      if (*(data + end_count) == '\0') {
      end_of_data = true;
      }
    }
    prev_is_deli = curr_is_deli;
    end_count++;
  }
  *size = size_of_arr;
  if (output_is_null) {
    delete[] array;
    return;
  }
  String *output_arr = new String[size_of_arr];
  for (size_t i = 0; i < (size_of_arr*2); i += 2) {
    char *sub_data = create_new_copy((data + array[i]), (array[i + 1] -
    array[i]));
    String sub_string(sub_data);
    output_arr[(i/2)] = sub_string;
    delete[] sub_data;
  }
  *output = output_arr;
  delete[] array;
}

int String::to_integer() const {
  return atoi(data);
 }

String String::trim() const {
  if (data == NULL) {
    return String();
  }
  if (data[0] == '\0') {
    String empty_String = *this;
    return empty_String;
  }
  int trim_begin = 0;
  int trim_end = length;
  while (data[trim_begin] == ' ') {
    if (data[trim_begin + 1] == '\0') {
      String empty_String = (data + trim_begin + 1);
      return empty_String;
    }
    trim_begin++;
  }
  while (data[trim_end - 1] == ' ') {
    trim_end--;
  }
  char *new_string = create_new_copy((data + trim_begin), (trim_end - trim_begin));
  String trimmed_String(new_string);
  delete[] new_string;
  return trimmed_String;
}
