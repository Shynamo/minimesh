#include "viewer.hpp"

#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOpenGLRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

void Viewer::view(vtkSmartPointer<vtkDataSet> dataset){
  // Mapper
  vtkSmartPointer<vtkPolyData> polyData
   = vtkSmartPointer<vtkPolyData>(vtkPolyData::SafeDownCast(dataset));
  vtkSmartPointer<vtkPolyDataMapper> mapper
   = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);

  // Actor
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetMapper()->ScalarVisibilityOff();

  // Renderer
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor
   = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);

  // Launch
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  renderWindowInteractor->Start();
}

