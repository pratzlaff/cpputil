#include <iostream>
#include "fs.hh"

using namespace std;

ostream& operator<<(ostream& s, const util::fs_entry& f)
{

  s << boolalpha;

  s << "Good: " << f.good() << '\n';
  if (f.good()) {
    s << "Name: " << f.name() << '\n';
    s << "Directory: " << f.dir() << '\n';
    s << "File: " << f.file() << '\n';
    s << "Size: " << f.size() << '\n';
  }
  s << noboolalpha;
  return s;
}

int main(int argc, char* argv[])
{

  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " file1 file2 ...\n";
    return EXIT_FAILURE;
  }

  for (int i=1; i<argc; ++i)
    cout << util::fs_entry(argv[i]) << '\n';

}
