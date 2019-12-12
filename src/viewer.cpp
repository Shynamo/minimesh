#include "viewer.hpp"

#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkOpenGLRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

void Viewer::view(vtkSmartPointer<vtkDataSet> dataset){
  // Mapper
  vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputData(dataset);
  mapper->ScalarVisibilityOff();

  // Actor
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->EdgeVisibilityOn();
  actor->GetProperty()->VertexVisibilityOn();

  // Renderer
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->UseHiddenLineRemovalOn();
  renderer->AddActor(actor);

  // Render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  // Interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor
   = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Launch
  renderWindowInteractor->Initialize();
  renderWindow->Render();
  renderWindowInteractor->Start();
}

