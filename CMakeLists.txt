cmake_minimum_required(VERSION 3.28)
project(Bugs LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
add_subdirectory(dependencies)

add_executable(Bugs "src/main.cpp" "src/defines.h" "src/game.cpp" "src/game.h" "src/bug.h" "src/bug.cpp")
if(WIN32)
	target_link_options(Bugs PRIVATE "$<IF:$<CONFIG:Debug>,/SUBSYSTEM:CONSOLE,/SUBSYSTEM:WINDOWS;/ENTRY:mainCRTStartup>")
	if(BUILD_SHARED_LIBS)
		add_custom_command(TARGET Bugs POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:ImGui-SFML::ImGui-SFML>
			$<TARGET_FILE:sfml-graphics>
			$<TARGET_FILE:sfml-window>
			$<TARGET_FILE:sfml-system>
			$<TARGET_FILE_DIR:Bugs>)
	endif()
endif()
target_compile_features(Bugs PRIVATE cxx_std_20)
target_link_libraries(Bugs PRIVATE ImGui-SFML::ImGui-SFML)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Bugs)
