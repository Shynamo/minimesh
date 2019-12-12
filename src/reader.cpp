#include "reader.hpp"
#include "misc.hpp"

#include <cstdlib>
#include <cstring>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyDataMapper.h>

vtkSmartPointer<vtkDataSet> Reader::read(std::string input_file){
  // Read data from file
  vtkSmartPointer<vtkXMLUnstructuredGridReader> reader =
    vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader->SetFileName(input_file.c_str());
  reader->Update();
  reader->GetOutput()->Register(reader);

  // Conversion to dataset
  vtkSmartPointer<vtkDataSet> dataset = 
    vtkSmartPointer<vtkUnstructuredGrid>(vtkUnstructuredGrid::SafeDownCast(reader->GetOutput()));
  return dataset;
}
