#include "lib.h"

#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_input_processing)
{

  std::string source = {"113.162.145.156	111	0"};
  std::vector<std::string> result = {"113.162.145.156", "111", "0"};
  
  BOOST_REQUIRE( split(source, '\t') == result);
  
  std::string ipSource = result.at(0);
  ip_adress ipSeparated{113, 162, 145, 156};
  
  BOOST_REQUIRE( getIpAdress(ipSource, '.') == ipSeparated );
}

BOOST_AUTO_TEST_SUITE_END()
