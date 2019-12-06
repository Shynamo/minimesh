#pragma once

#include <vtkSmartPointer.h>
#include <vtkDataReader.h>

// Viewer is used only to view data
// The data should be already formated into a grid
class Viewer
{
public:
  Viewer(void) {}
  ~Viewer(void) {}

  void view(vtkSmartPointer<vtkDataSet>);
};
