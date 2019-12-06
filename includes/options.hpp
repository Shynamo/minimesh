#pragma once

#include <memory>

#include "cpptoml.h"
#include "transform.hpp"

class OptionsParser
{
public:
  OptionsParser(const std::string&);
  ~OptionsParser(void) {}

  struct Params parse();

private:
  std::string m_file_name;
  std::shared_ptr<cpptoml::table> m_data;
};
