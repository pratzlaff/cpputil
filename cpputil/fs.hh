#ifndef UTIL_FS_HH
#define UTIL_FS_HH

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace util {

  class fs_entry {

    struct stat s_;
    const std::string name_;
    bool good_;

  public:

    class sentry {
      const fs_entry& f_;
    public:
      sentry(const fs_entry& f) : f_(f) { }
      operator bool() { return f_.good(); }
    };

    fs_entry(const std::string& name) : name_(name)
    {
      good_ = !stat(name.c_str(), &s_);
    }

    bool good() const { return good_; }
    operator bool() const { return good(); }

    const std::string& name() const { return name_; }

    bool dir() const {
      if (sentry(*this))
	return S_ISDIR(s_.st_mode);
      else
	return false;
    }

    bool file() const {
      if (sentry(*this))
	return S_ISREG(s_.st_mode);
      else
	return false;
    }

    std::size_t size() const {
      if (sentry(*this))
	return s_.st_size;
      else
	return 0;
    }

  };

} // namespace util

#endif // UTIL_FS_HH
