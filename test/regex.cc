#include <cpputil/cpputil.hh>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {

  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " pattern text" << endl;
    exit(EXIT_FAILURE);
  }

  try {

    util::regex re(argv[1], util::regex::comp_ext | util::regex::comp_nocap);
    const char *text = argv[2];

    if (re.exec(text)) {
      cout << "matched" << endl;
      for (vector<string>::const_iterator it=re.captured().begin();
	   it != re.captured().end();
	   ++it)
	cout << *it << endl;
    }
    else {
      cout << "did not match" << endl;
    }

    
  }

  catch(std::exception &e) {
    cerr << e.what() << endl;
    exit(EXIT_FAILURE);
  }

}
