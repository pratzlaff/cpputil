#ifndef UTIL_SEQUENCE_HH
#define UTIL_SEQUENCE_HH

namespace util {

  template<typename T>
  class sequence {

  private:
    T _start, _inc;

  public:

    sequence(T start=0, T inc=1)
      : _start(start-inc), _inc(inc)
    {
    }

    T operator()()
    {
      return _start += _inc;
    }

  };

}

#endif
