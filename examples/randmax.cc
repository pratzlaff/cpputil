#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cpputil/cpputil.hh>

using namespace std;

int main() {

  typedef vector<int> VType;

  VType v;

  // fill the container with a simple sequence
  generate_n(std::back_inserter(v), 10, util::sequence<int>(0,5));

  cout << "Before: ";
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
  cout << endl;

  // shuffle values around
  const util::rand_max<VType::difference_type> r;
  random_shuffle(v.begin(), v.end(), r);

  cout << "After:  ";
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
  cout << endl;

}
