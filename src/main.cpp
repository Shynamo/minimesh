#include "options.hpp"
#include "misc.hpp"
#include "quality.hpp"
#include "viewer.hpp"
#include "reader.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>


using namespace std;

void print_usage()
{
  cout << "A VTK-focused unstructured mesh manipulation mini-app\n";
  cout << "Usage:\n";
  cout << "  minimesh [OPTION...]\n";
  cout << "\n";
  cout << "  -v, --view Mesh file            View a mesh\n";
  cout << "  -t, --transform Transform file  Transform (merge, translate) a mesh\n";
  cout << "  -h, --help                      Print help\n";
}

int main(int argc, char **argv)
{
  string command;
  string file_name;

  if (argc > 1) {
    command = argv[1];
  }

  /*  Retrieving command line arguments
      Setting up file_name and params */
  if ((argc <= 1) || command == "-h" || command == "--help") {
    print_usage();
    return EXIT_SUCCESS;
  }

  /*  Viewer Setup */
  if (command == "-v" || command == "--view") {
    if (argc < 3) {
      cerr << "Error: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    if (!has_extension(file_name, "vtu") && !has_extension(file_name, "vtk")){
      cerr << "Error: unsupported format. Please use .vtu or .vtk files.\n";
      return EXIT_FAILURE;
    }
    
    Reader *reader = new Reader();
    vtkSmartPointer<vtkDataSet> dataset = reader->read(file_name);

    Viewer *viewer = new Viewer();
    viewer->view(dataset);

    delete reader;
    delete viewer;

  /*  Transform Setup */
  } else if (command == "-t" || command == "--transform") {
    if (argc < 3) {
      cerr << "Error: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    OptionsParser *op = new OptionsParser(file_name);
    auto params = op->parse();
    delete op;
    //TODO: tester le type de retour cout << typeof(params) << endl;
    // TODO: test if input filenamesare supported


    //test TRANS_MERGE, TRANS_TRANSLATION

  /*  Error case */
  } else {
    cerr << "Error: unknown command\n";
    print_usage();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

















/* 
TP1 Python Code
    #### PIPELINE
    # Reading data
    reader = vtk.vtkXMLImageDataReader()
    reader.SetFileName("data/head.vti")
    reader.Update()

    # Getting "head" scalar data
    head = reader.GetOutput().GetPointData().GetScalars("head")

    lookupTable = vtk.vtkLookupTable()
    lookupTable.SetRange(head.GetRange())
    lookupTable.Build()

    # Creating isocontour of isovalue from read data
    isovalue = float(50)
    isoSurfaceContour = vtk.vtkContourFilter()
    isoSurfaceContour.SetInputConnection(reader.GetOutputPort())
    isoSurfaceContour.SetValue(0, isovalue)

    # Creating mapper from isocontour
    mapper = vtk.vtkPolyDataMapper()
    mapper.SetInputConnection(isoSurfaceContour.GetOutputPort())
    mapper.SetScalarRange(lookupTable.GetRange())

    # Creating actor from isocontour
    actor = vtk.vtkActor()
    actor.SetMapper(mapper)
    actor.GetProperty().SetColor(1,1,1)

    # Using OpenGL renderer and linking with previous actors
    renderer = vtk.vtkOpenGLRenderer()
    renderer.AddActor(actor)
    #renderer.AddActor(sliderWidget)
    renderer.SetBackground(0, 0, 0)

    # Initializing render window linked with previous renderer
    window = vtk.vtkRenderWindow()
    window.AddRenderer(renderer)
    window.SetSize(800, 800)

    interactor = vtk.vtkRenderWindowInteractor()
    interactor.SetRenderWindow(window)
    
    # Creating colored scalar bar widget
    scalarBarActor = vtk.vtkScalarBarActor()
    scalarBarActor.SetLookupTable(lookupTable)
    scalarBarWidget = vtk.vtkScalarBarWidget()
    scalarBarWidget.SetInteractor(interactor)
    scalarBarWidget.SetScalarBarActor(scalarBarActor)
    scalarBarWidget.On()

    # Creating slide bar
    sliderRep = vtk.vtkSliderRepresentation2D()
    sliderRep.SetTitleText("Contour value")
    sliderRep.SetLabelHeight(0.05)
    sliderRep.SetSliderWidth(0.1)
    sliderRep.GetPoint1Coordinate().SetCoordinateSystemToNormalizedViewport()
    sliderRep.GetPoint1Coordinate().SetValue(0.1, 0.1)
    sliderRep.GetPoint2Coordinate().SetCoordinateSystemToNormalizedViewport()
    sliderRep.GetPoint2Coordinate().SetValue(0.3, 0.1)
    sliderRep.SetMinimumValue(head.GetRange()[0])
    sliderRep.SetMaximumValue(head.GetRange()[-1])

    def SliderCallback(obj, event):
        sliderRep = obj.GetRepresentation()
        pos = sliderRep.GetValue()
        isoSurfaceContour.SetValue(0, pos)

    sliderWidget = vtk.vtkSliderWidget()
    sliderWidget.SetInteractor(interactor)
    sliderWidget.SetRepresentation(sliderRep)
    sliderWidget.On()
    sliderWidget.AddObserver(vtk.vtkCommand.InteractionEvent, SliderCallback)

    # Launching render window
    interactor.Initialize()
    window.Render()
    interactor.Start()
 */
