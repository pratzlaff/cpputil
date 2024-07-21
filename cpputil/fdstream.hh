#ifndef UTIL_FDSTREAM_HH
#define UTIL_FDSTREAM_HH

#include <streambuf>
#include <iosfwd>
#include <iostream>

extern "C" {
#include <unistd.h>
}

namespace util {

  class fdstreambuf_error { };


  class fdoutbuf : public std::streambuf
  {

  protected:
    int _fd;

    int_type overflow(int_type c) throw(fdstreambuf_error)
    {
      std::cerr << "overflow\n";
      if (traits_type::eof() == c)
	return c;

      if (write(_fd, &c, 1) == 1)
	return traits_type::not_eof(c);
      else
	throw fdstreambuf_error();
    }

    std::streamsize xsputn(const char_type *data, std::streamsize n)
      throw(fdstreambuf_error)
    {
      std::cerr << "xsputn\n";
      int retval = write(_fd, data, n);
      if (retval >= 0)
	return retval;
      else 
	throw fdstreambuf_error();
    }

  public:
    explicit fdoutbuf(int fd) : _fd(fd) { ; }

  };

  class fdostream : public std::ostream
  {
  protected:
    fdoutbuf _buf;
  public:
    explicit fdostream(int fd) : std::ostream(0), _buf(fd)
    {
      rdbuf(&_buf);
    }
  };

}

#endif // UTIL_FDSTREAM_HH
