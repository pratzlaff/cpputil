#ifndef UTIL_FMT_HH
#define UTIL_FMT_HH

#include <ostream>
#include <string>
#include <stdexcept>

namespace util {


  /** Thrown when an invalid printf-style format string is specified.
   */
  class fmt_error : public std::invalid_argument
  {
  public:
    fmt_error(const std::string& msg)
      : std::invalid_argument(msg)
    { }
  };

  /**
   * Encapsulates information for setting stream format state.
   *
   * This class is used internally by the two util::fmt manipulators.
   * The ctor takes a printf-style format string (for a single
   * argument) and can later use that information to set format
   * state on a stream via the apply() member.
   */
  class fmt_description {
    enum { none, right, left } justify;
    bool alternate_form;
    bool show_positive;
    int width;
    int precision;
    char fill;
    char conversion;

    void parse(const char* s);

  public:
    /**
     * Constructor accepts printf-style format string.
     */
    fmt_description(const char* s);

    /**
     * Set stream formatting state.
     */
    std::ostream& apply(std::ostream& io) const;
      
  };

  /**
   * Manipulator irreversibly sets the stream format state.
   */
  fmt_description fmt(const std::string& str);
  fmt_description fmt(const char* str);
  std::ostream& operator<<(std::ostream& o, const fmt_description& f);

  template<typename OutT>
  struct fmt_struct
  {
    fmt_description fdescr;
    const OutT& arg;
    fmt_struct(const char* s, const OutT& arg)
      : fdescr(s), arg(arg)
    { }
  };


  /**
   * Manipulator inserts argument and restores stream format state.
   */
  template<typename OutT>
  fmt_struct<OutT> fmt(const std::string& str, const OutT& arg)
  {
    return fmt_struct<OutT>(str.c_str(), arg);
  }
  template<typename OutT>
  fmt_struct<OutT> fmt(const char* str, const OutT& arg)
  {
    return fmt_struct<OutT>(str, arg);
  }

  template<typename OutT>
  std::ostream& operator<<(std::ostream& o, const fmt_struct<OutT>& f)
  {
    std::ios_base::fmtflags orig_flags = o.flags();
    const char orig_fill = o.fill();
    const std::streamsize orig_precision = o.precision();

    f.fdescr.apply(o);
    o << f.arg;

    o.flags(orig_flags);
    o.fill(orig_fill);
    o.precision(orig_precision);

    return o;
  }

} // namespace util

#endif // UTIL_FMT_HH
