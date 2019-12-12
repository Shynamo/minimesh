#include "options.hpp"
#include "misc.hpp"
#include "quality.hpp"
#include "viewer.hpp"
#include "reader.hpp"
#include "transform.hpp"

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

  /* Helper */
  if ((argc <= 1) || command == "-h" || command == "--help") {
    print_usage();
    return EXIT_SUCCESS;
  }

  /* =========== VIEWER =========== */

  /*  Viewer Setup */
  if (command == "-v" || command == "--view") {
    /* Idiot proof checking */
    if (argc < 3) {
      cerr << "ERROR: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    if (!file_exists(file_name)){
      cerr << "ERROR: File " << file_name << " doesn't exist.\n";
      print_usage();
      return EXIT_FAILURE;
    }
    if (!has_extension(file_name, "vtu") && !has_extension(file_name, "vtk")){
      cerr << "ERROR: unsupported format. Please use .vtu or .vtk files.\n";
      print_usage();
      return EXIT_FAILURE;
    }
    
    /* Reading and Viewing data */
    Reader *reader = new Reader();
    vtkSmartPointer<vtkDataSet> dataset = reader->read(file_name);
    delete reader;

    Viewer *viewer = new Viewer();
    viewer->view(dataset);
    delete viewer;

  /* =========== TRANSFORM =========== */

  /*  Transform Setup */
  } else if (command == "-t" || command == "--transform") {
    if (argc < 3) {
      cerr << "ERROR: missing file.\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    OptionsParser *op = new OptionsParser(file_name);
    Params *params = op->parse();
    delete op;

    /* Error case for parsing */
    if (params == nullptr){
      cerr << "ERROR: couldn't parse input file.\n";
      print_usage();
      return EXIT_FAILURE;
    }

    /* Reading Input File */
    Reader *reader = new Reader();
    vtkSmartPointer<vtkDataSet> dataset = reader->read(file_name);
    delete reader;

    /* Applying Transformation */
    if (params->transform == TRANS_MERGE){
      MergeParams *mparams = dynamic_cast<MergeParams*>(params);
      /* Dynamic cast error */
      if (mparams == nullptr){
        cerr << "ERROR: Parameters conversion error.\n";
        return EXIT_FAILURE;
      }

      cout << "TANS MERGE\n";
      //TODO: transform


    } else if (params->transform == TRANS_TRANSLATION){
      TranslationParams *tparams = dynamic_cast<TranslationParams*>(params);
      /* Dynamic cast error */
      if (tparams == nullptr){
        cerr << "ERROR: Parameters conversion error.\n";
        return EXIT_FAILURE;
      }

      //TODO: transform
      cout << "TANS TRANS\n";

    /* Error case */
    } else {
      cerr << "ERROR: Invalid transformation.\n";
      print_usage();
      return EXIT_FAILURE;
    }

    /* Visualizing data */
    vtkSmartPointer<vtkDataSet> transformed_dataset = nullptr; //TODO: Implement transformation
    Viewer *viewer = new Viewer();
    //viewer->view(transformed_dataset);
    delete viewer;

  /*  Error case */
  } // End transform
  else {
    cerr << "ERROR: unknown command\n";
    print_usage();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
