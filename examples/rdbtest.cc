#include <cpputil/rdb.hh>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <typeinfo>

using namespace std;

ostream& operator<<(ostream& s, const map<string,vector<string> >& m) 
{
  // no data
  if (m.empty())
    return s;

  // make vectors of the column names and vectors
  vector<const string*> names;
  vector<const vector<string>* > data;
  for (map<string,vector<string> >::const_iterator it = m.begin(); it!=m.end(); ++it) {
    names.push_back(&(it->first));
    data.push_back(&(it->second));
  }

  // print the header
  for (vector<const string*>::const_iterator it=names.begin(); it!=names.end()-1; ++it)
    s << **it << '\t';
  s << **(names.end()-1) << '\n';
  for (vector<const string*>::const_iterator it=names.begin(); it!=names.end()-1; ++it)
    s << string((**it).size(), '-') << '\t';
  s << string((**(names.end()-1)).size(), '-') << '\n';

  // print data
  size_t n1 = (*data[0]).size();
  size_t n2 = names.size();
  for (size_t i=0; i<n1; ++i) {
    for (size_t j=0; j<n2-1; ++j)
      s << (*data[j])[i] << '\t';
    s << (*data[n2-1])[i] << '\n';
  }

  return s;
}

int main(int argc, char* argv[])
{

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " file\n";
    return EXIT_FAILURE;
  }

  try {
    map<string,vector<string> > rdb;
    util::rdb_read(argv[1], rdb);
    cout << rdb;
  }
  catch (const exception& e) {
    cerr << "Exception caught ("
	 << typeid(e).name() << ") - " << e.what() <<'\n';
    return EXIT_FAILURE;
  }

}
