#ifndef UTIL_FMT_UNIT_HH
#define UTIL_FMT_UNIT_HH
#define UNIT_CLASS fmt_unit

#include <cppunit/extensions/HelperMacros.h>
#include <sstream>
#include <iostream>
#include <cpputil/fmt.hh>

namespace util {

  class UNIT_CLASS : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( UNIT_CLASS );

    CPPUNIT_TEST( tests );

    CPPUNIT_TEST_EXCEPTION( bad_format1, util::fmt_error );
    CPPUNIT_TEST_EXCEPTION( bad_format2, util::fmt_error );
    CPPUNIT_TEST_EXCEPTION( bad_format3, util::fmt_error );

    CPPUNIT_TEST_SUITE_END();

  private:
    std::ostringstream o;

  public:

    void bad_format1() throw(util::fmt_error) { o << util::fmt(""); }
    void bad_format2() throw(util::fmt_error) { o << util::fmt("a"); }
    void bad_format3() throw(util::fmt_error) { o << util::fmt("b"); }

    void tests()
    {

      // right justification
      o.str(""); o << util::fmt("%2d", 5);
      CPPUNIT_ASSERT(o.str() == " 5");
      o.str(""); o << util::fmt("%5.2f", 5.0);
      CPPUNIT_ASSERT(o.str() == " 5.00");
      //      o.str(""); o << util::fmt("%3.2d", 5);
      //      CPPUNIT_ASSERT(o.str() == " 05");

      // left justification
      o.str(""); o << util::fmt("%-2d", 5);
      CPPUNIT_ASSERT(o.str() == "5 ");
      o.str(""); o << util::fmt("%-5.2f", 5.0);
      CPPUNIT_ASSERT(o.str() == "5.00 ");
      //      o.str(""); o << util::fmt("%-3.2d", 5);
      //      CPPUNIT_ASSERT(o.str() == "05 ");


    }

  };

  CPPUNIT_TEST_SUITE_REGISTRATION( UNIT_CLASS );

}

#undef UNIT_CLASS

#endif
