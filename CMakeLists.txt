cmake_minimum_required(VERSION 3.2)

project(hw7)

find_package(GTest REQUIRED)

add_executable(containers_tests
               tests/SerialContainer_tests.cpp)
target_include_directories(containers_tests
               PRIVATE
               "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(containers_tests
                      GTest::gtest
                      GTest::gtest_main
                      gmock)
