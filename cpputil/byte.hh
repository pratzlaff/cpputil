#ifndef UTIL_BYTE_HH
#define UTIL_BYTE_HH

#include <cstddef>

#include "cpputil/types.hh"

namespace util {

  /// Returns true if system has big endian byte ordering.
  bool isbigendian();

  /// forward declare bswap so we can use in bswap_one_element
  template<typename T> inline void bswap(T* begin, T* end);

  /// Byte swap a single element whose sizeof==n, specializations
  /// exist for sizeof == 1, 2, 4 and 8.
  template<std::size_t n>
  inline void bswap_one_element(void *ptr)
  {
    unsigned char tmp;
    unsigned char *buf = reinterpret_cast<unsigned char*>(ptr);
    for (std::size_t i=0; i<n/2; ++i) {
      tmp = buf[i];
      buf[i] = buf[n-i-1];
      buf[n-i-1] = tmp;
    }
  }

  template<>
  inline void bswap_one_element<2>(void* p)
  {
    uint16 *ptr = reinterpret_cast<uint16*>(p);
    *ptr = ((*ptr)<<8) | ((*ptr)>>8);
  }

  template<>
  inline void bswap_one_element<4>(void* p)
  {
    uint32 *ptr = reinterpret_cast<uint32*>(p);
    *ptr =
      ((*ptr)>>24) |
      (((*ptr)>>8)&0x0000ff00) |
      (((*ptr)<<8)&0x00ff0000) |
      ((*ptr)<<24);
  }

  template<>
  inline void bswap_one_element<8>(void* p)
  {
    uint32 *ptr = reinterpret_cast<uint32*>(p);
    bswap(ptr, ptr+2);
    uint32 tmp = *ptr;
    *ptr = *(ptr+1);
    *(ptr+1) = tmp;
  }

  template<>
  inline void bswap_one_element<1>(void*)
  {
  }

  template<std::size_t stride, typename It>
  inline void bswap(It begin, It end)
  {
    for (It it = begin; it < end; ++it)
      bswap_one_element<stride>(&(*it));
  }

  template<typename T>
  inline void bswap(T* begin, T* end)
  {
    for (T* ptr = begin; ptr<end; ++ptr)
      bswap_one_element<sizeof(T)>(ptr);
  }

  template<typename T>
  inline void bswap(T& in)
  {
    bswap_one_element<sizeof(T)>(&in);
  }

} // namespace util

#endif // UTIL_BYTE_HH
