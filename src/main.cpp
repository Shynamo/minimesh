#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

#include "options.hpp"

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

  if (command == "-v" || command == "--view") {
    if (argc < 3) {
      std::cerr << "Error: missing file\n";
      print_usage();
      return EXIT_FAILURE;
    }
    file_name = argv[2];
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
  } else {
    std::cerr << "Error: unknown command\n";
    print_usage();
    return EXIT_FAILURE;
  }

  /*  Main process */


  return EXIT_SUCCESS;
}
