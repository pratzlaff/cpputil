#ifndef UTIL_MEM_DATA_HH
#define UTIL_MEM_DATA_HH

#include <functional>

namespace util {
  template<typename Result, typename Ty>
  class mem_data_t : public std::unary_function<Ty*, Result>
  {
    const Result Ty::*pm_;
  public:
    mem_data_t(const Result Ty::*pm) : pm_(pm) {}
    Result operator()(const Ty* left) const
    {
      return left->*pm_;
    }
  };

  template<class Result, class Ty>
  mem_data_t<Result, Ty> mem_data(Result Ty::*pm)
  {
    return mem_data_t<Result, Ty>(pm);
  }
  
  template<typename Result, typename Ty>
  class mem_data_ref_t : public std::unary_function<Ty, Result>
  {
    const Result Ty::*pm_;
  public:
    mem_data_ref_t(const Result Ty::*pm) : pm_(pm) {}
    Result operator()(const Ty& left) const
    {
      return left.*pm_;
    }
  };

  template<class Result, class Ty>
  mem_data_ref_t<Result, Ty> mem_data_ref(Result Ty::*pm)
  {
    return mem_data_ref_t<Result, Ty>(pm);
  }

} // namespace util

#endif // UTIL_MEM_DATA_HH
