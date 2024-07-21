//#include <cpputil/cpputil.hh>
#include <cpputil/mem_data.hh>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <functional>

using namespace std;
using namespace util;

struct foo { int i; };

int main(int argc, char **argv) {

  vector<foo> f;
  sort(f.begin(), f.end(), less<int>(mem_data_ref(&foo::i), 0));


}
