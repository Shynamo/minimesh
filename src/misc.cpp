#include "misc.hpp"

#include <cstdlib>
#include <string>
#include <vector>

bool has_extension(std::string file_name, std::string extension){
  return file_name.substr(file_name.find_last_of(".") + 1) == extension;
}