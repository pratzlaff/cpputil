#ifndef UTIL_SINGLETON_UNIT_HH
#define UTIL_SINGLETON_UNIT_HH
#define UNIT_CLASS singleton_unit

#include <cppunit/extensions/HelperMacros.h>
#include <cpputil/singleton.hh>

namespace util {

  class UNIT_CLASS : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( UNIT_CLASS );

    CPPUNIT_TEST( test );

    CPPUNIT_TEST_SUITE_END();

  private:

  public:

    void test()
    {
      util::singleton<int>::instance() = 5;
      int &i = util::singleton<int>::instance();
      i = 10;
      CPPUNIT_ASSERT( util::singleton<int>::instance() == 10 );
    }

  };

  CPPUNIT_TEST_SUITE_REGISTRATION( UNIT_CLASS );

}

#undef UNIT_CLASS

#endif
