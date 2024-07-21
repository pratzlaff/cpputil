#ifndef UTIL_RDB_HH
#define UTIL_RDB_HH

#include <map>
#include <string>
#include <vector>
#include <stdexcept>

namespace util {

  class rdb_error : public std::runtime_error {
  public:
    rdb_error(const std::string &s = "unknown RDB error")
      : std::runtime_error(s)
    { }
  };

  void rdb_read(const std::string& filename,
		std::map<std::string, std::vector<std::string> >& output,
		const std::vector<std::string>& cols_to_read
		= std::vector<std::string>()
		) throw(rdb_error);
}

#endif // UTIL_RDB_HH
