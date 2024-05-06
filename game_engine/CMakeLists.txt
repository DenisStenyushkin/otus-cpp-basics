cmake_minimum_required(VERSION 3.22)

project(guess_number.game_engine)

add_library(
    game_engine

    STATIC

    game_engine.h
    game_engine.cpp
)

target_include_directories(
    game_engine

    PUBLIC

    ../args
)

# target_link_libraries(
#     game_engine
#     args
# )
