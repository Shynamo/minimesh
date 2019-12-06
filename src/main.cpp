#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>
//#include <vtk>

#include "options.hpp"
#include "misc.hpp"

void print_usage()
{
  std::cout << "A VTK-focused unstructured mesh manipulation mini-app\n";
  std::cout << "Usage:\n";
  std::cout << "  minimesh [OPTION...]\n";
  std::cout << "\n";
  std::cout << "  -v, --view Mesh file            View a mesh\n";
  std::cout << "  -t, --transform Transform file  Transform (merge, translate) a mesh\n";
  std::cout << "  -h, --help                      Print help\n";
}

int main(int argc, char **argv)
{
  std::string command;
  std::string file_name;

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
      std::cerr << "Error: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    if (!has_extension(file_name, "vtu") && !has_extension(file_name, "vtk")){
      std::cerr << "Error: unsupported format. Please use .vtu or .vtk files.\n";
      return EXIT_FAILURE;
    }


  /*  Transform Setup */
  } else if (command == "-t" || command == "--transform") {
    if (argc < 3) {
      std::cerr << "Error: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
    OptionsParser *op = new OptionsParser(file_name);
    struct Params params = op->parse();
    delete op;
    // TODO: test if input filenamesare supported


    //test TRANS_MERGE, TRANS_TRANSLATION

  /*  Error case */
  } else {
    std::cerr << "Error: unknown command\n";
    print_usage();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
