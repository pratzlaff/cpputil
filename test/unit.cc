#include <cstdlib>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "fmt_unit.hh"
#include "cast_unit.hh"
#include "singleton_unit.hh"
#include "str_unit.hh"
#include "byte_unit.hh"

int main()
{
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest( registry.makeTest() );
  bool wasSucessful = runner.run( "", false );
  return wasSucessful ? EXIT_SUCCESS : EXIT_FAILURE;
}
