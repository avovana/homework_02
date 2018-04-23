cmake_minimum_required(VERSION 3.2)

# check environment variable TRAVIS_BUILD_NUMBER
if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

project(ipfilter  VERSION 0.0.${VERSION_BUILD})

# set variables for directories with source code
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/tests")

find_package(Boost COMPONENTS unit_test_framework)

add_executable(ip_filter 
	${SOURCE_PATH}/ipfilter.cpp
	${SOURCE_PATH}/lib.h
	${SOURCE_PATH}/filter_func.h
	${SOURCE_PATH}/utils.h)

add_executable(test_func ${TEST_PATH}/test_functions.cpp)

set_target_properties(
  ip_filter
  test_func
  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(test_func
  PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    INCLUDE_DIRECTORIES ${SOURCE_PATH}
)

target_link_libraries(test_func
  ${Boost_LIBRARIES}
  functions_lib 
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT vladimir.englisbox@gmail.com)

include(CPack)

enable_testing()
add_test(test_input_processing test_func)
