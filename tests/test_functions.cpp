#include "lib.h"
#include "filter_func.h"

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

BOOST_AUTO_TEST_CASE(test_filter_1)
{
	std::vector<ip_adress> ip_pool_input = {
		std::make_tuple(192,168,46,1), 
		std::make_tuple(192,168,0,2), 
		std::make_tuple(192,168,0,1), 
		std::make_tuple(192,167,0,1),
		std::make_tuple(191,168,0,1), 
		std::make_tuple(72,46,0,1), 
		std::make_tuple(46,168,0,1), 
		std::make_tuple(46,70,46,2), 
		std::make_tuple(46,70,46,1), 
		std::make_tuple(46,70,43,2), 
		std::make_tuple(1,168,0,1),
		std::make_tuple(1,2,0,1)
	};  
	
	std::vector<ip_adress> filtered = ipFilter(ip_pool_input, FILTER_MATCH::IN_ORDER, 1);
	
	std::vector<ip_adress> result = {
		std::make_tuple(1,168,0,1), 
		std::make_tuple(1,2,0,1)
	};	
	
	BOOST_REQUIRE( filtered == result);
	
	std::vector<ip_adress> resultWrong = {
		std::make_tuple(192,168,46,1), 
		std::make_tuple(192,168,0,2)
	};	

	BOOST_REQUIRE( filtered != resultWrong);
}

BOOST_AUTO_TEST_CASE(test_filter_46_70)
{
	std::vector<ip_adress> ip_pool_input = {
		std::make_tuple(192,168,46,1), 
		std::make_tuple(192,168,0,2), 
		std::make_tuple(192,168,0,1), 
		std::make_tuple(192,167,0,1),
		std::make_tuple(191,168,0,1), 
		std::make_tuple(72,46,0,1), 
		std::make_tuple(46,168,0,1), 
		std::make_tuple(46,70,46,2), 
		std::make_tuple(46,70,46,1), 
		std::make_tuple(46,70,43,2), 
		std::make_tuple(1,168,0,1),
		std::make_tuple(1,2,0,1)
	};  
	
	std::vector<ip_adress> filtered = ipFilter(ip_pool_input, FILTER_MATCH::IN_ORDER, 46, 70);
	
	std::vector<ip_adress> result = {
		std::make_tuple(46,70,46,2), 
		std::make_tuple(46,70,46,1), 
		std::make_tuple(46,70,43,2)
	};	
	
	BOOST_REQUIRE( filtered == result);
	
	std::vector<ip_adress> resultWrong = {
		std::make_tuple(46,70,46,2), 
		std::make_tuple(192,168,0,2)
	};	

	BOOST_REQUIRE( filtered != resultWrong);
}

BOOST_AUTO_TEST_CASE(test_filter_any_46)
{
	std::vector<ip_adress> ip_pool_input = {
		std::make_tuple(192,168,46,1), 
		std::make_tuple(192,168,0,2), 
		std::make_tuple(192,168,0,1), 
		std::make_tuple(192,167,0,1),
		std::make_tuple(191,168,0,1), 
		std::make_tuple(72,46,0,1), 
		std::make_tuple(46,168,0,1), 
		std::make_tuple(46,70,46,2), 
		std::make_tuple(46,70,46,1), 
		std::make_tuple(46,70,43,2), 
		std::make_tuple(1,168,0,1),
		std::make_tuple(1,2,0,1)
	};  
	
	std::vector<ip_adress> filtered = ipFilter(ip_pool_input, FILTER_MATCH::ANY_OF, 46);
	
	std::vector<ip_adress> result = {
		std::make_tuple(46,168,0,1), 
		std::make_tuple(46,70,46,2), 
		std::make_tuple(46,70,46,1), 
		std::make_tuple(46,70,43,2)
	};	
	
	BOOST_REQUIRE( filtered == result);
	
	std::vector<ip_adress> resultWrong = {
		std::make_tuple(45,168,0,1), 
		std::make_tuple(46,70,46,2), 
		std::make_tuple(46,70,46,1), 
		std::make_tuple(46,70,43,2),
	};	

	BOOST_REQUIRE( filtered != resultWrong);
}

BOOST_AUTO_TEST_SUITE_END()
