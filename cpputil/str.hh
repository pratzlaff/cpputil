#ifndef UTIL_STR_HH
#define UTIL_STR_HH

#include <string>

namespace util {

  std::string str2hex(const std::string&);
  std::string hex2str(const std::string&);
  std::string lc(std::string);
  std::string uc(std::string);
  std::string strip(std::string);

}
#endif // UTIL_STR_HH
