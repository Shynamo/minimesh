#include "misc.hpp"

#include <cstdlib>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

bool has_extension(string file_name, string extension){
  return file_name.substr(file_name.find_last_of(".") + 1) == extension;
}

bool file_exists(const string& name){
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}