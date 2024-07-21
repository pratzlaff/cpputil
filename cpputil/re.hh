#ifndef UTIL_RE_HH
#define UTIL_RE_HH

extern "C" {
#include <regex.h>
}
#include <string>
#include <vector>
#include <stdexcept>

namespace util {

  class regex {

  public:

    class compile_error : public std::invalid_argument {
    public:
      explicit compile_error(std::string msg = "") throw()
	: std::invalid_argument(msg)
      { }
    };
    
    class capture_error : public std::logic_error {
    public:
      explicit capture_error(std::string msg = "") throw()
	: std::logic_error(msg)
      { }
    };
    
    /** @var typedef int cflags
     * @brief Regular expression compilation flags
     */
    typedef int cflags;
    static const cflags comp_ext   = 1<<0;
    static const cflags comp_icase = 1<<1;
    static const cflags comp_nocap = 1<<2;
    static const cflags comp_mline = 1<<3;

    /// Compile a regular expression for later use
    /**
     * @param s The regular expression to compile
     * @param flags 
     */
    regex(const char *s, cflags flags=0) throw(compile_error)
      : preg(0), matches(0), posix_flags(0), comp_flags(flags)
    {
      init(s);
    }

    /// Execute without capture
    /**
     * @see exec()
     * @param s The string to match against
     * @return Whether the input string matched
     */
    bool match(const char *s) throw() {
      if (regexec(preg, s, 0, 0, 0))
	return false;
      else
	return true;
    }

    /// Execute with capture
    /**
     * @see match()
     * @see captured()
     * @param s The string to match against
     * @return Whether the input string matched
     */
    bool exec(const char *s) throw() {

      if (regexec(preg, s, nmatches, matches, 0))
	return false;

      if (!(comp_flags & comp_nocap)) {

	for (int i=0; i<nmatches; ++i) {
	  if (matches->rm_so != -1)
	    captures[i] = std::string(s+matches[i].rm_so,
				      matches[i].rm_eo - matches[i].rm_so);
	  else
	    captures[i].clear();
	}

      }
      return true;
    }

    /// Return captured strings
    /**
     * @see exec()
     * @return vector of captured strings
     */
    const std::vector<std::string>& captured() throw(capture_error)
    {
      if (comp_flags & comp_nocap)
	throw capture_error("capturing disabled");
      return captures;
    }
	

    ~regex() throw() {
      regfree(preg);
      delete preg;
      delete matches;
    }

  private:

    regex_t *preg;
    int nmatches;
    regmatch_t *matches;

    std::vector<std::string> captures;

    static const int errbuf_size = 256;
    char errbuf[errbuf_size];

    int posix_flags;
    cflags comp_flags;

    regex& operator=(const regex&);
    regex(const regex&);

    void init(const char *pattern) throw(compile_error) {

      if (comp_flags & comp_ext)   posix_flags |= REG_EXTENDED;
      if (comp_flags & comp_icase) posix_flags |= REG_ICASE;
      if (comp_flags & comp_nocap) posix_flags |= REG_NOSUB;
      if (comp_flags & comp_mline) posix_flags |= REG_NEWLINE;

      preg = new regex_t;

      if (int errcode = regcomp(preg, pattern, posix_flags)) {
	regerror(errcode, preg, errbuf, errbuf_size);
	throw compile_error(errbuf);
      }
      else {
	if (!(comp_flags & comp_nocap)) {
	  nmatches = preg->re_nsub+1;
	  matches = new regmatch_t[nmatches];
	  captures.resize(nmatches);
	}
      }

    }

  };

}

#endif // UTIL_RE_HH
