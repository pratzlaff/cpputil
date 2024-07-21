#ifndef UTIL_CAST_UNIT_HH
#define UTIL_CAST_UNIT_HH
#define UNIT_CLASS cast_unit_foo

#include <cppunit/extensions/HelperMacros.h>
#include <cpputil/ss_cast.hh>

namespace util {

  class UNIT_CLASS : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( UNIT_CLASS );

    CPPUNIT_TEST( test );

    CPPUNIT_TEST_SUITE_END();

  private:

  public:

    void test()
    {

      CPPUNIT_ASSERT( util::ss_cast<int>("1234") == 1234 );
      CPPUNIT_ASSERT( util::ss_cast<int>("Hello") == 0 );
      CPPUNIT_ASSERT( util::ss_cast<int>("Hello", 9999) == 9999 );

    }

  };

  CPPUNIT_TEST_SUITE_REGISTRATION( UNIT_CLASS );

}

#undef UNIT_CLASS

#endif
