#include "transform.hpp"
#include "misc.hpp"
#include "reader.hpp"

#include <cstdlib>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkAppendPolyData.h>
//#include <vtkCleanGrid.h>
#include <vtkUnstructuredGridBaseAlgorithm.h>
#include <vtkXMLUnstructuredGridWriter.h>

using namespace std;

MergeTransform::MergeTransform(struct Params *params):Transform(){
  this->_params = dynamic_cast<MergeParams*>(params); // nullptr is failed
}

TranslationTransform::TranslationTransform(struct Params *params):Transform(){
  this->_params = dynamic_cast<TranslationParams*>(params); // nullptr is failed
}

void Transform::setParams(struct Params *params){
  this->_params = params;
}

bool Transform::saveOutput(){
  if (this->_dataset == nullptr || this->_params == nullptr) { return false; }
  //if (file_exists(this->_params->output)) { return false; }
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer
    = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(this->_params->output.c_str());

  return writer->Write() == 1 ? true : false;
}

bool Transform::getOutput(){
  return this->_dataset;
}

/* Merge Transform */
vtkSmartPointer<vtkDataSet> 
MergeTransform::start(){
  if (this->_params){ return nullptr; }
  //FIXME
  /* Adding every input to the filter */
  vtkSmartPointer<vtkUnstructuredGridBaseAlgorithm> gridAlgorithm
    = vtkSmartPointer<vtkUnstructuredGridBaseAlgorithm>::New();
  //vtkSmartPointer<vtkCleanGrid> cleanFilter;
  Reader *reader = new Reader();
  for (auto &input: this->_params->input){
    gridAlgorithm->AddInputData(reader->read(input));
  }
  
  /* Remove any duplicate points */
  /* cleanFilter = vtkSmartPointer<vtkCleanGrid>::New();
  cleanFilter->SetInputConnection(gridAlgorithm->GetOutputPort());
  cleanFilter->Update();
  this->_dataset = vtkSmartPointer<vtkDataSet>(cleanFilter->GetOutputPort()); */

  delete reader;

  return this->_dataset;
}

/* Translation Transform */
vtkSmartPointer<vtkDataSet> 
TranslationTransform::start(){
  if (this->_params){ return nullptr; }

  Reader *reader = new Reader();
  this->_dataset = reader->read(this->_params->input);  
  delete reader;

  //TODO

  return this->_dataset;
}

