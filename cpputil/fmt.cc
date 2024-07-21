#include <cpputil/fmt.hh>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <cstring>

namespace util {

  fmt_description fmt(const char* str)
  {
    return fmt_description(str);
  }

  fmt_description fmt(const std::string& str)
  {
    return fmt_description(str.c_str());
  }

  std::ostream& operator<<(std::ostream& o, const fmt_description& f)
  {
    f.apply(o);
    return o;
  }

  fmt_description::fmt_description(const char* s)
  {
    parse(s);
  }

  std::ostream& fmt_description::apply(std::ostream& io) const
  {

    if (conversion == 'X' ||
	conversion == 'O' ||
	conversion == 'E' ||
	conversion == 'F' ||
	conversion == 'G' ||
	0)
      io << std::uppercase;
    else
      io << std::nouppercase;

    if (conversion == 'O' || conversion == 'o')
      io << std::oct;
    if (conversion == 'X' || conversion == 'x')
      io << std::hex;

    switch (conversion) {

    case 's':
    case 'd':
    case 'i':
      break;

    case 'O':
    case 'o':
    case 'X':
    case 'x':
      if (alternate_form)
	io << std::showbase;
      break;

    case 'f':
    case 'F':
      io << std::fixed;
      break;

    case 'e':
    case 'E':
      io << std::scientific;
      break;

    case 'g':
    case 'G':
      io.unsetf(std::ios_base::floatfield);
      break;

    default:
      assert(0);
    }

    return io << std::setfill(fill)
	      << (justify==none ? std::internal :
		  justify==right ? std::right : std::left)
	      << std::setw(width)
	      << std::setprecision(precision)
	      << (show_positive ? std::showpos : std::noshowpos)
      ;
  }

  void fmt_description::parse(const char* str)
  {
    justify = none;
    alternate_form = false;
    show_positive = false;
    width = 0;
    precision = 6;
    fill = ' ';
    conversion = 's';

    std::size_t strn = std::strlen(str);

    enum { FLAGS, WIDTH, PDOT, PRECISION } at;
    at = FLAGS;

    // beginning % is optional, skip it
    if (strn && str[0] == '%')
      ++str, --strn;

    if (!strn)
      throw fmt_error("invalid format");

    // get the conversion specifier
    const char conversions[] =
      { 'd', 'i', 'o', 'x', 'X', 'e', 'E', 'f', 'F', 'g', 'G', 's' };
    const char* conversions_end = conversions+sizeof(conversions);
    const char* conv_at = std::find(conversions,
				    conversions_end,
				    str[strn-1]
				    );
    if (conv_at == conversions_end)
      throw fmt_error(std::string("invalid conversion character '")+str[strn-1]+'\'');
    conversion = str[strn-1];

    for (const char* it=str; it<str+strn-1; ++it) {
      switch (at) {

      case FLAGS:
	if ( *it >= '1' && *it <= '9' ) { // started width segment
	  at = WIDTH;
	  width = *it - '0';
	}
	else if ( *it == '.' ) // started precision segment
	  at = PDOT;
	else {
	  switch (*it) {
	  case '#':
	    alternate_form = true; break;
	  case '0':
	    fill = '0'; break;
	  case '-':
	    justify = left; break;
	  case '+':
	    show_positive = true; break;
	  default:
	    throw fmt_error(std::string("invalid flag character '")+*it+'\'');
	  }
	}
	break;

      case WIDTH:
	if (*it == '.') // started precision segment
	  at = PDOT;
	else if (*it >= '0' && *it <= '9') {
	  width *= 10;
	  width += *it - '0';
	}
	else
	  throw fmt_error(std::string("invalid width character '")+*it+'\'');
	break;

      case PDOT:
	at = PRECISION;
	if (*it >= '0' && *it <= '9')
	  precision = *it - '0';
	else
	  throw fmt_error(std::string("invalid precision character '")+*it+'\'');
	break;

      case PRECISION:
	if (*it < '0' || *it > '9')
	  throw fmt_error(std::string("invalid precision character '")+*it+'\'');
	precision *= 10;
	precision += *it - '0';
	break;

      default:
	assert(0);

      }

    }
  }

} // namespace util

