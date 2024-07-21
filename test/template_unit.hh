//
// replace these defines
//
#ifndef UTIL_TEMPLATE_UNIT_HH
#define UTIL_TEMPLATE_UNIT_HH
#define UNIT_CLASS template_unit

#include <cppunit/extensions/HelperMacros.h>

namespace util {

  class UNIT_CLASS : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( UNIT_CLASS );

    //
    // the more the merrier
    //
    CPPUNIT_TEST( normal_test );
    CPPUNIT_TEST_EXCEPTION( exception_test, int );

    CPPUNIT_TEST_SUITE_END();

  private:

  public:

    void normal_test()
    {
      CPPUNIT_ASSERT( 1 );
    }

    void exception_test() throw(int)
    {
      throw 0;
    }

  };

  CPPUNIT_TEST_SUITE_REGISTRATION( UNIT_CLASS );

}

#undef UNIT_CLASS

#endif
