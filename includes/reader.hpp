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

  vtkSmartPointer<vtkDataSet> view(std::string input_file);
};
