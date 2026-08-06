cmake_minimum_required(VERSION 3.28)
project(Bugs LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
add_subdirectory(dependencies)

if(WIN32)
	set(SUBSYSTEM_LINKER_OPTIONS "$<IF:$<CONFIG:Debug>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS;/ENTRY:mainCRTStartup>")
else()
	set(SUBSYSTEM_LINKER_OPTIONS "$<IF:$<NOT:$<CONFIG:Debug>>,-mwindows,>")
endif()

add_executable(Bugs src/main.cpp "src/defines.h"  "src/game.cpp" "src/game.h" "src/bug.h"   "src/bug.cpp")
target_link_options(Bugs PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})
target_compile_features(Bugs PRIVATE cxx_std_20)
target_link_libraries(Bugs PRIVATE ImGui-SFML::ImGui-SFML)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Bugs)
