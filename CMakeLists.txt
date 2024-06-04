cmake_minimum_required(VERSION 3.12)

project(hw6)

add_executable(main
               main.cpp
               IContainer.hpp
               SerialContainer.hpp
               LinkedListContainer.hpp
               ReservingSerialContainer.hpp
               DoubleLinkedListContainer.hpp)

set_target_properties(main 
                      PROPERTIES CXX_STANDARD 17 
                      CXX_STANDARD_REQUIRED ON)

if(MSVC)
        target_compile_options(main PUBLIC /W4 /WX)
else()
        target_compile_options(main PUBLIC -Wall -Wextra -Werror -pedantic)
endif()
