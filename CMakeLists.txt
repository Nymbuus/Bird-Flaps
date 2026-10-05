cmake_minimum_required(VERSION 3.20)

project(Bird-Flaps LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------
# Raylib
# --------------------------------------------------

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)

# Don't build Raylib's example programs
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

# --------------------------------------------------
# Our executable
# --------------------------------------------------

add_executable(Bird-Flaps
    "src/main.cpp" "src/Game.cpp" "src/Game.h" "src/Player.cpp" "src/Pipe.cpp" "src/Score.cpp" "src/Score.h")

add_custom_command(TARGET Bird-Flaps POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Bird-Flaps>/assets"
)

# Link Raylib to our program
target_link_libraries(Bird-Flaps PRIVATE raylib)