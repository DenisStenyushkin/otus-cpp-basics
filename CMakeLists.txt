cmake_minimum_required(VERSION 3.12)

project(hw8)

find_package(Threads REQUIRED)

add_executable(main
               topk_words_async.cpp)
target_link_libraries(main PUBLIC Threads::Threads)

set_target_properties(main 
                      PROPERTIES CXX_STANDARD 17 
                      CXX_STANDARD_REQUIRED ON)

if(MSVC)
        target_compile_options(main PUBLIC /W4 /WX)
else()
        target_compile_options(main PUBLIC -Wall -Wextra -Werror -pedantic)
endif()
