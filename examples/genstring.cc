#include <iostream>
#include <string>

#include <cpputil/rand.hh>
#include <cpputil/ss_cast.hh>

// generate and output a random string of alphanumeric characters

int main(int argc, char* argv[]) {

  int n=8;

  if (argc > 1)
    n = util::ss_cast<int>(argv[1]);

  std::string c
    = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  std::string gen;

  util::rand_max<std::size_t> r;

  for (int i=0; i<n; ++i)
    gen.append( 1, c[ r( c.length() ) ] );

  std::cout << gen << std::endl;

}
