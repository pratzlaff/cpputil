#include <iostream>
#include <cpputil/cpputil.hh>

using namespace std;
using namespace util::term;

int main() {
  //cout << red << "Red" << endl;
  //cout << bold << "Bold" << endl;
  //cout << blink << "Blink" << endl;
  //cout << dim << "Dim" << endl;
  //cout << reverse << "reverse" << endl;
  //cout << reset;
  cout << color(yellow, magenta) << "yellow on magenta" << endl;
  cout << reset;
}
