cmake_minimum_required(VERSION 3.22)

project(guess_number.args)

add_library(
    args

    STATIC

    args.h
    args.cpp
)

add_executable(args_test args_test.cpp)
target_link_libraries(args_test args)
