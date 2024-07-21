#ifndef UTIL_SS_CAST_HH
#define UTIL_SS_CAST_HH

#include <sstream>

namespace util {

  template<typename OutT, typename InT>
  OutT ss_cast(const InT& in, const OutT& badval = OutT()) {
    std::stringstream ss;
    OutT out = badval;
    ss << in;
    ss >> out;
    return out;
  }

} // namespace util

#endif // UTIL_SS_CAST_HH
