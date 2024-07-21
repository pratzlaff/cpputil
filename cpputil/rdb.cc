#include <cpputil/rdb.hh>
#include <cpputil/ss_cast.hh>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <stdexcept>

namespace util {

  using std::vector;
  using std::string;
  using std::map;
  using std::size_t;
  using std::ifstream;
  using std::istringstream;

  void rdb_read(
		const string& filename,
		map<string, vector<string> >& output,
		const vector<string>& cols_to_read
		) throw(rdb_error)
  {
    ifstream in(filename.c_str());

    // could not open input file
    if (!in)
      throw(rdb_error("could not open '" + filename + '\''));

    string line;
    vector<string> cols;
    vector<vector<string>* > data_ptrs;

    // mask of which existing columns we will be reading
    vector<int> cols_read_mask;

    // mask of which requested columns were found
    vector<int> good_input_cols(cols_to_read.size(), 0);

    // skip initial comments
    size_t line_num = 0;
    while (getline(in,line)) {
      ++line_num;

      // invalid line
      if (!line.size())
	throw(rdb_error(filename + " has empty line"));

      // found end of comments, read the column names and next dummy line
      if (line[0] != '#') {
	istringstream ss(line);
	string column;
	size_t i = 0;
	while (getline(ss, column, '\t')) {

	  cols.push_back(column);
	  cols_read_mask.push_back(0);
	  data_ptrs.push_back(0);

	  vector<string>::const_iterator it =
	    find(cols_to_read.begin(), cols_to_read.end(), column); 

	  if (!cols_to_read.size() ||
	      it != cols_to_read.end() ) {
	    good_input_cols[distance(cols_to_read.begin(),it)] = 1;
	    data_ptrs[i]  = &(output[column]);
	    cols_read_mask[i] = 1;
	  }

	  ++i;
	}

	if (!getline(in, line))
	  throw(rdb_error(filename + " appears truncated"));

	++line_num;

	break; // done reading header
      }
    }

    // throw an exception if one of the requested columns wasn't in the file
    vector<int>::iterator it
      = find(good_input_cols.begin(), good_input_cols.end(), 0);
    if (it != good_input_cols.end()) {
      string colname = cols_to_read[distance(good_input_cols.begin(), it)];
      throw std::runtime_error(string("requested column '") + colname + "' was not found in " + filename);
    }


    size_t ncols = cols.size();
    while (getline(in, line)) {
      size_t i = 0;
      ++line_num;

      // using the getline(stringstrem, line, '\t') method is much easier,
      // but appears to take twice as long
      string::size_type next_tab, last_tab=0;

      do {

	next_tab = line.find('\t', last_tab);

	if (i == ncols)
	  throw(rdb_error(filename +
			  ": too many columns in line " +
			  ss_cast<string>(line_num)
			  ));

	if (cols_read_mask[i])
	  data_ptrs[i]->push_back(line.substr(last_tab, next_tab-last_tab));

	++i;
	last_tab = next_tab+1;

      } while (next_tab != line.npos);

      if (i != ncols)
	throw(rdb_error(filename +
			": not enough columns in line " +
			ss_cast<string>(line_num)
			));

      /*
      std::istringstream ss(line);
      std::string data;
      while (getline(ss, data, '\t')) {

	// did we read one too many columns?
	if (i == ncols)
	  throw(rdb_error(filename + " too many columns found"));

	data_ptrs[i]->push_back(data);
	++i;
      }
      */

      // did the line have enough columns?
      if (i != ncols)
	throw(rdb_error(filename + " not enough columns found"));
    }
      
  }

} // namespace util
