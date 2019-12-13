#include "transform.hpp"
#include "misc.hpp"
#include "reader.hpp"

#include <cstdlib>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkAppendPolyData.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkAppendFilter.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkGeneralTransform.h>
#include <vtkTransformFilter.h>
#include <vtkMeshQuality.h>

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

void Transform::computeQuality(void){
  /* Il aurait mieux valu mettre cette methode dans une autre classe
    et ne l'appeller que si besoin dans cette classe. Cela permettrait
    d'appliquer le contrôle de qualité même sur des DataSets n'ayant rien à voir
    avec une transformation.
    Mais il se fait tard, donc j'ai choisi la solution de facilité en la mettant ici.
  */

  vtkSmartPointer<vtkMeshQuality> qualityFilter =
    vtkSmartPointer<vtkMeshQuality>::New();
  qualityFilter->SetInputData(this->_dataset);
  qualityFilter->SetTriangleQualityMeasureToShapeAndSize();
  qualityFilter->Update();
  
  this->_dataset->ShallowCopy(qualityFilter->GetOutput());
}

bool Transform::saveOutput(){
  if (this->_dataset == nullptr || this->_params == nullptr) { return false; }
  if (file_exists(this->_params->output)) { return false; }
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer
    = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(this->_params->output.c_str());
  writer->SetInputData(this->_dataset);

  return writer->Write() == 1 ? true : false;
}

bool Transform::getOutput(){
  return this->_dataset;
}

/* Merge Transform */
vtkSmartPointer<vtkDataSet> 
MergeTransform::start(){
  if (this->_params == nullptr){ return nullptr; }

  /* Adding every input to the filter */
  auto datasets = new vtkSmartPointer<vtkXMLUnstructuredGridReader>[this->_params->input.size()];
  vtkSmartPointer<vtkAppendFilter> filter
   = vtkSmartPointer<vtkAppendFilter>::New();

  filter->SetMergePoints(this->_params->merge_nodes);

  int i = 0;
  for (auto &input: this->_params->input){
    datasets[i] = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    datasets[i]->SetFileName(input.c_str());
    datasets[i]->Update();
    filter->AddInputConnection(datasets[i]->GetOutputPort());
    filter->Update();
    i++;
  }

  delete[] datasets;

  this->_dataset = vtkSmartPointer<vtkDataSet>(vtkUnstructuredGrid::SafeDownCast(filter->GetOutput()));
  if (this->_params->compute_quality){
    this->computeQuality();
  }

  return this->_dataset;
}

/* Translation Transform */
vtkSmartPointer<vtkDataSet> 
TranslationTransform::start(){
  cerr << this->_params << endl;
  if (this->_params == nullptr){ return nullptr; }
  vtkSmartPointer<vtkXMLUnstructuredGridReader> reader
   = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader->SetFileName(this->_params->input.c_str());
  reader->Update();

  vtkSmartPointer<vtkGeneralTransform> transfo
    = vtkSmartPointer<vtkGeneralTransform>::New();
  transfo->Translate(this->_params->coords[0], 
                     this->_params->coords[1], 
                     this->_params->coords[2]);
  
  vtkSmartPointer<vtkTransformFilter> transfoFilter
    = vtkSmartPointer<vtkTransformFilter>::New();
  transfoFilter->SetInputConnection(reader->GetOutputPort());
  transfoFilter->SetTransform(transfo);
  transfoFilter->Update();

  this->_dataset = vtkSmartPointer<vtkDataSet>(vtkDataSet::SafeDownCast(transfoFilter->GetOutput()));

  if (this->_params->compute_quality){
    this->computeQuality();
  }

  return this->_dataset;
}

