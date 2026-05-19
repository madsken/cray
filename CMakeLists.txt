cmake_minimum_required(VERSION 3.16)

project(cray C)

set(CMAKE_C_STANDARD 99)

find_package(raylib REQUIRED)

# --- engine ---
add_executable(engine
    src/main.c
)

target_link_libraries(${PROJECT_NAME} raylib dl)

# --- game module (hot reload) ---
add_library(game SHARED
    src/game.c
)

target_link_libraries(game raylib)
set_target_properties(game PROPERTIES OUTPUT_NAME "game")
