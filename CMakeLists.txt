cmake_minimum_required(VERSION 3.22)

project(guess_number.homework)

add_executable(game
    game.cpp
)

set_target_properties(game PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
)

add_subdirectory(args)
add_subdirectory(game_engine)
add_subdirectory(rng)
add_subdirectory(scores)

target_include_directories(game PRIVATE args)
target_include_directories(game PRIVATE game_engine)
target_include_directories(game PRIVATE rng)
target_include_directories(game PRIVATE scores)

target_link_libraries(game
    args
    game_engine
    rng
    scores
)
