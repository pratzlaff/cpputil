#include <iostream>
#include <string>
#include <cpputil/cpputil.hh>

int main(int argc, char** argv) {

  util::fdostream ofd(1);

  char c = 'H';
  ofd << 'h' << "ello world\n";

}
