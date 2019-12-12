#include "viewer.hpp"

#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOpenGLRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>

void Viewer::view(vtkSmartPointer<vtkDataSet> dataset){
  // Mapper
  vtkSmartPointer<vtkPolyData> polyData
   = vtkSmartPointer<vtkPolyData>(vtkPolyData::SafeDownCast(dataset));
  vtkSmartPointer<vtkPolyDataMapper> mapper
   = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);
  mapper->ScalarVisibilityOff();

  // Actor
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetSpecular(.3);
  actor->GetProperty()->SetSpecularPower(30);
  actor->GetProperty()->EdgeVisibilityOn();

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

