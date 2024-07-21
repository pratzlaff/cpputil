#include <exception>
#include <cpputil/cpputil.hh>
#include <iostream>
#include <string>

class test_exception1 : public util::exception {
public:
  test_exception1() : util::exception("a test") { }
};

void foo1() {
  throw test_exception1();
}

class test_exception2 : public util::exception {
};

void foo2() {
  throw test_exception2();
}

int main() {
  try {
    foo1();
  }
  catch(std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    foo2();
  }
  catch(std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
      
