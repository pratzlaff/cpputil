#ifndef UTIL_FACTORIAL_HH
#define UTIL_FACTORIAL_HH

namespace util {

  template<unsigned long N>
  struct factorial {
    static const unsigned long value = ::util::factorial<N-1>::value * N;
  };

  template <>
  struct factorial<0> {
    static const unsigned long value = 1;
  };
}

#endif // UTIL_FACTORIAL_HH
