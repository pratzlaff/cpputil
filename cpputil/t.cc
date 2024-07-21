#include <iostream>
#include <cstdlib>
#include <exception>
#include "fmt.hh"
#include "ss_cast.hh"


int main(int argc, char* argv[]) {

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " format double\n";
    return EXIT_FAILURE;
  }

  try {
    double d = util::ss_cast<double>(argv[2]);
    std::cout << util::fmt(argv[1], d) << '\n';
    std::cout << d << '\n';
    std::cout << util::fmt(argv[1]) << d << '\n';
  }
  catch(std::exception &e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  
}
