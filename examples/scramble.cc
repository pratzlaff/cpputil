#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <cstddef>
#include <cpputil/rand.hh>

int main() {

  std::vector<std::string> lines;
  std::string tmp;
  while(getline(std::cin, tmp))
    lines.push_back(tmp);

  util::rand_max<std::ptrdiff_t> r;

  random_shuffle(lines.begin(), lines.end(), r);

  copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

}
  
