#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cpputil/byte.hh>

namespace util {
  bool isbigendian()
  {

#ifdef HAVE_CONFIG_H

#ifdef WORDS_BIGENDIAN
    return true;
#else
    return false;
#endif

#else
    int i = 1;
    return !*(reinterpret_cast<char*>(&i));
#endif

  }
}

