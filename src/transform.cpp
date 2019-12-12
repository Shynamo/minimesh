#include "transform.hpp"
#include "misc.hpp"
#include "reader.hpp"

#include <cstdlib>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>

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
  if (this->_dataset == nullptr || this->_params){ return false; }
  //if (file_exists(this->_params->output)) { return false; }
  cout << "TODO: Implement saveFile method.\n";
  //TODO
  return true;
}

/* Merge Transform */
vtkSmartPointer<vtkDataSet> 
MergeTransform::start(){
  if (this->_params){ return nullptr; }
  Reader *reader = new Reader();
  vtkSmartPointer<vtkDataSet> dataset 
    = reader->read(this->_params->output);
  delete reader;
  //TODO
  return dataset;
}

/* Translation Transform */
vtkSmartPointer<vtkDataSet> 
TranslationTransform::start(){
  if (this->_params){ return nullptr; }
  Reader *reader = new Reader();
  vtkSmartPointer<vtkDataSet> dataset 
    = reader->read(this->_params->output);
  delete reader;
  //TODO
  return dataset;
}

