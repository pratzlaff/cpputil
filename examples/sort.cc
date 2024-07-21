#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {

  std::vector<std::string> v;
  std::string tmp;
  while (getline(std::cin, tmp))
    v.push_back(tmp);

  sort(v.begin(), v.end());

  copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
