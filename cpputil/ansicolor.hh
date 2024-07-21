#ifndef UTIL_ANSICOLOR_H
#define UTIL_ANSICOLOR_H

#include <ostream>
#include <iosfwd>

namespace util {

  namespace term {

    inline std::ostream& reset(std::ostream &s) { return s << "\033[0m"; }
    inline std::ostream& bold(std::ostream &s) { return s << "\033[1m"; }
    inline std::ostream& dim(std::ostream &s) { return s << "\033[2m"; }
    inline std::ostream& underline(std::ostream &s) { return s << "\033[4m"; }
    inline std::ostream& blink(std::ostream &s) { return s << "\033[5m"; }
    inline std::ostream& reverse(std::ostream &s) { return s << "\033[7m"; }
    inline std::ostream& hidden(std::ostream &s) { return s << "\033[8m"; }

    inline int black()   { return 0; }
    inline int red()     { return 1; }
    inline int green()   { return 2; }
    inline int yellow()  { return 3; }
    inline int blue()    { return 4; }
    inline int magenta() { return 5; }
    inline int cyan()    { return 6; }
    inline int white()   { return 7; }

    struct cattr {
      int fg;
      int bg;
    };

    template<typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& s, const cattr& a) {
      return s << "\033[" << a.fg << ';' << a.bg << 'm';
    }

    typedef int(*cfunc)();
    inline cattr color(cfunc f, cfunc b) {
      cattr ret;
      ret.fg = f() + 30;
      ret.bg = b() + 40;
      return ret;
    }

    inline std::ostream& black(std::ostream &s)   { return s << "\033[30m"; }
    inline std::ostream& red(std::ostream &s)     { return s << "\033[31m"; }
    inline std::ostream& green(std::ostream &s)   { return s << "\033[32m"; }
    inline std::ostream& yellow(std::ostream &s)  { return s << "\033[33m"; }
    inline std::ostream& blue(std::ostream &s)    { return s << "\033[34m"; }
    inline std::ostream& magenta(std::ostream &s) { return s << "\033[35m"; }
    inline std::ostream& cyan(std::ostream &s)    { return s << "\033[36m"; }
    inline std::ostream& white(std::ostream &s)   { return s << "\033[37m"; }

  }

}

#endif // UTIL_ANSICOLOR_H
