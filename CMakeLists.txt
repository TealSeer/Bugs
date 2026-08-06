cmake_minimum_required(VERSION 3.28)
project(Bugs LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Bugs src/main.cpp "src/defines.h"  "src/game.cpp" "src/game.h" "src/bug.h"   "src/bug.cpp")
target_compile_features(Bugs PRIVATE cxx_std_20)
target_link_libraries(Bugs PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Bugs)
