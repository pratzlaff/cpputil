#ifndef UTIL_STR_UNIT_HH
#define UTIL_STR_UNIT_HH
#define UNIT_CLASS str_unit

#include <cppunit/extensions/HelperMacros.h>
#include <cpputil/str.hh>

namespace util {

  class UNIT_CLASS : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( UNIT_CLASS );

    CPPUNIT_TEST( lc );
    CPPUNIT_TEST( uc );
    CPPUNIT_TEST( strip );

    CPPUNIT_TEST_SUITE_END();

  private:

  public:

    void lc() {
      CPPUNIT_ASSERT(util::lc("FoO") == "foo");
      CPPUNIT_ASSERT(util::lc("") == "");
    }

    void uc() {
      CPPUNIT_ASSERT(util::uc("FoO") == "FOO");
      CPPUNIT_ASSERT(util::uc("") == "");
    }

    void strip() {
      CPPUNIT_ASSERT(util::strip(" a b c ") == "a b c");
      CPPUNIT_ASSERT(util::strip(" a b c") == "a b c");
      CPPUNIT_ASSERT(util::strip("a b c ") == "a b c");
      CPPUNIT_ASSERT(util::strip("a b c") == "a b c");
      CPPUNIT_ASSERT(util::strip("") == "");
    }

  };

  CPPUNIT_TEST_SUITE_REGISTRATION( UNIT_CLASS );

}

#undef UNIT_CLASS

#endif
