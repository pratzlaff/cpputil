#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cpputil/str.hh>

namespace {
  inline int my_classic_tolower(int c) { return std::tolower(c); }
  inline int my_classic_toupper(int c) { return std::toupper(c); }
}

namespace util {

  std::string str2hex(const std::string& s) {
    std::ostringstream oss;
    oss.fill('0');
    oss.setf(std::ios_base::hex, std::ios_base::basefield);
    for (std::string::const_iterator it = s.begin(); it!=s.end(); ++it)
      oss << std::setw(2) << int(*it);
    return oss.str();
  }

  std::string hex2str(const std::string& h) {
    std::string s;
    for (std::string::const_iterator it = h.begin(); it<h.end(); it+=2) {
      int i;
      std::istringstream iss(std::string(it, it+2));
      iss.setf(std::ios_base::hex, std::ios_base::basefield);
      iss >> i;
      s += char(i);
    }
  }

  std::string lc(std::string s) {
    transform(s.begin(), s.end(), s.begin(), my_classic_tolower);
    return s;
  }

  std::string uc(std::string s) {
    transform(s.begin(), s.end(), s.begin(), my_classic_toupper);
    return s;
  }

  std::string strip(std::string s) {
    s.erase(0,s.find_first_not_of("\r\n\v\t\f "));
    s.erase(s.find_last_not_of("\r\n\v\t\f ")+1, s.npos);
    return s;
  }

}
