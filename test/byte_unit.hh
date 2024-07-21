#ifndef UTIL_TEMPLATE_UNIT_HH
#define UTIL_TEMPLATE_UNIT_HH
#define UNIT_CLASS byte_unit

#include <cppunit/extensions/HelperMacros.h>

#include <cpputil/byte.hh>
#include <cstring>

namespace util {

  class UNIT_CLASS : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE( UNIT_CLASS );

    CPPUNIT_TEST( test_swap_general );
    CPPUNIT_TEST( test_swap_two );
    CPPUNIT_TEST( test_swap_four );
    CPPUNIT_TEST( test_swap_eight );

    CPPUNIT_TEST_SUITE_END();

  private:

  public:

    void test_swap_general() throw()
    {
      char foo[] = "foo";
      bswap_one_element<3>(foo);
      CPPUNIT_ASSERT(std::strcmp(foo, "oof") == 0);
    }

    void test_swap_two() throw()
    {
      util::uint16 j;

      j = 0x0001;
      util::bswap(&j,1);
      CPPUNIT_ASSERT( j==0x0100 );

      j = 0x0100;
      util::bswap(&j, 1);
      CPPUNIT_ASSERT( j==0x0001 );
    }

    void test_swap_four() throw()
    {
      util::uint32 i;

      i = 0x00000001;
      util::bswap(&i, 1);
      CPPUNIT_ASSERT( i==0x01000000 );

      i = 0x00000100;
      util::bswap(&i, 1);
      CPPUNIT_ASSERT( i==0x00010000 );

      i = 0x00010000;
      util::bswap(&i, 1);
      CPPUNIT_ASSERT( i==0x00000100 );

      i = 0x01000000;
      util::bswap(&i, 1);
      CPPUNIT_ASSERT( i==0x00000001 );
    }

    void test_swap_eight() throw()
    {
      util::uint64 k = 1;
      util::bswap(&k, 1);
      CPPUNIT_ASSERT( (k>>56) == 1 );
    }

  };

  CPPUNIT_TEST_SUITE_REGISTRATION( UNIT_CLASS );

}

#undef UNIT_CLASS

#endif
