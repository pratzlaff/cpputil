#ifndef UTIL_MATH_HH
#define UTIL_MATH_HH

#include <cstdlib>
#include <cmath>
#include <numeric>
#include <vector>
#include <utility>

namespace util {

  /**
   *  @brief Calculate statistics in a range.
   *
   *  Calculates simple statistics for a collection of values.
   *
   **/
  template<typename T, typename It>
  std::vector<T> stats(It begin, It end)
  {
    std::vector<T> stats(7);
    if (begin == end) return stats;

    // make a copy so we can sort for median determination
    std::vector<T> c(begin, end);

    // get the median
    T median;
    sort(c.begin(), c.end());
    typename std::vector<T>::size_type n = c.size();
    typename std::vector<T>::const_iterator it = c.begin();

    if (n % 2) { // odd number of elements
      advance(it, n/2);
      median = *it;
    }
    else {       // even number of elements
      advance(it, n/2-1);
      median = *it++;
      median = (median + *it)/2;
    }

    // calculate the mean
    T mean = accumulate(c.begin(), c.end(), T()) / n;

    // now we loop through once more, getting the other statistics
    T rms = T();
    T adev = T();
    for (it=c.begin(); it!=c.end(); ++it) {
      T diff = *it - mean;
      rms += diff * diff;
      adev += std::abs(diff);
    }

    T prms = std::sqrt(rms / (n-1));
    rms = std::sqrt(rms / n);
    adev /= n;

    stats[0] = mean;
    stats[1] = prms;
    stats[2] = median;
    stats[3] = c[0];
    stats[4] = c[c.size()-1];
    stats[5] = adev;
    stats[6] = rms;

    return stats;
  }

  // specialization for standard containers
  template<typename T, template<typename> class C>
  std::vector<T> stats(const C<T>& c)
  {
    return stats<T>(c.begin(), c.end());
  }

  // specialization for pointer
  template<typename T>
  std::vector<T> stats(T* begin, T* end)
  {
    return stats<T>(begin, end);
  }


  template<typename T, typename It1, typename It2>
  std::vector<T> rld(It1 nbegin, It1 nend, It2 valbegin)
  {
    std::vector<T> vals;
    It1 nit = nbegin;
    It2 valit = valbegin;
    for ( ; nit<nend; ++nit, ++valit)
      fill_n(back_inserter(vals), *nit, *valit);
    return vals;
  }

  // specialization for containers
  template<typename ValType, typename NType, template<typename> class NC, template<typename> class ValsC >
  std::vector<ValType> rld(const NC<NType>& n, const ValsC<ValType>& vals)
  {
    return rld<ValType>(n.begin(), n.end(), vals.begin());
  }

  // specialization for pointers
  template<typename ValType, typename NType>
  std::vector<ValType>
  rld(const NType* nbegin, const NType* nend, const ValType* valbegin)
  {
    return rld<ValType, NType const*, ValType const*>(nbegin, nend, valbegin);
  }

  template <typename T, typename It>
  std::pair< std::vector<std::size_t>, std::vector<T> >
  rle(It begin, It end)
  {

    std::pair< std::vector<std::size_t>, std::vector<T> > retval;
    std::vector<std::size_t> &n = retval.first;
    std::vector<T> &vals = retval.second;

    if (begin == end) return retval;

    T lastval = *begin;
    std::size_t lastn = 0;

    for (It it=begin; it<end; ++it, ++lastn) {
      if (*it != lastval) {
	n.push_back(lastn);
	vals.push_back(lastval);
	lastval = *it;
	lastn = 0;
      }
    }

    n.push_back(lastn);
    vals.push_back(lastval);

    return retval;
    
  }

  // specialization for containers
  template <typename T, template <typename> class C>
  std::pair< std::vector<std::size_t>, std::vector<T> >
  rle(const C<T>& c)
  {
    return rle<T>(c.begin(), c.end());
  }

  // specialization for pointers
  template<typename T>
  std::pair< std::vector<std::size_t>, std::vector<T> >
  rle(const T* begin, const T* end)
  {
    return rle<T>(begin, end);
  }

}

#endif // UTIL_MATH_HH
