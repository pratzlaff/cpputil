#ifndef UTIL_SINGLETON_HH
#define UTIL_SINGLETON_HH

namespace util {

  template<typename T>
  class singleton {
    
  private:

    //
    // there's actually no such thing as an instance of this class
    //

    singleton();
    singleton(const singleton<T>&);

  public:

    static T& instance() {
      static T _instance;
      return _instance;
    }
  
  };

}

#endif
