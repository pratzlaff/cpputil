#ifndef UTIL_RAND_HH
#define UTIL_RAND_HH

#include <cstdlib>

namespace util {
  
  /// Whether to call srand() the first time an instance of util::rand_max
  /// is instantiated.
  ///
  /// The default behaviour is for util::call_srand to begin as true. When
  /// an instance of util::rand_max is created, util::call_srand is checked, and if
  /// true, srand(time(0)) is called, whereupon util::call_srand becomes
  /// false. Thereafter srand() will not be called again.
  ///
  /// \warning If the (predictable) default seeding with srand(time(0))
  ///          is deemed unacceptable for your application, you should set
  ///          util::call_srand=false before creating any instances
  ///          of util::rand_max, and seed the random number generator manually
  ///          yourself with a suitable argument.
  ///
  extern volatile bool call_srand;

  /// Used internally by the util::rand_max ctor.
  void srand_init();
  
  /// A random number generating functor.
  ///
  /// \example
  ///  fill a container with a simple sequence, then shuffle the values
  ///  see examples/randmax.cc for the full code
  ///
  /// std::vector<int> v;
  /// generate_n(std::back_inserter(v), 10, util::sequence<int>(0,5));
  /// util::rand_max<std::vector<int>::difference_type> r;
  /// random_shuffle(v.begin(), v.end(), r);
  ///
  template<typename T>
  class rand_max {

  public:

    rand_max() {
      if (call_srand)
	srand_init();
    }

    /// Returns random value in half open range [0, max)
    T operator()(T max) const {
      return T(max * (std::rand()/(RAND_MAX+1.)));
    }

  };

}

#endif
