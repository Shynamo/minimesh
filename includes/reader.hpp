#pragma once

#include <cstdlib>
#include <cstring>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>

class Reader
{
public:
  Reader(void) {}
  ~Reader(void) {}

  vtkSmartPointer<vtkDataSet> read(std::string input_file);
};
