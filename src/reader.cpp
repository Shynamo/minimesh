#include "reader.hpp"

#include <cstdlib>
#include <cstring>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>

vtkSmartPointer<vtkDataSet> Reader::view(std::string input_file){
  // TODO
  (void) input_file;
  return vtkSmartPointer<vtkDataSet>();
}

