cmake_minimum_required(VERSION 3.16)
project(AudioVisualizer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# SFML setup
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.0
    GIT_SHALLOW FALSE
    GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(SFML)

# main program setup
set(VISUALIZER_H
    include/common.h
    include/graph.h
    include/visualizer.h
    include/imguiWindow.h
)

set(VISUALIZER_CPP
    src/visualizer.cpp
    src/graph.cpp
    src/imguiWindow.cpp
)

add_subdirectory(imgui)
target_link_libraries(imgui PUBLIC sfml-graphics sfml-system)


add_library(VISUALIZER STATIC ${VISUALIZER_H} ${VISUALIZER_CPP})
target_include_directories(VISUALIZER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(VISUALIZER PUBLIC sfml-graphics sfml-system sfml-audio imgui)

add_executable(AudioVisualizer main.cpp)
target_link_libraries(AudioVisualizer PUBLIC VISUALIZER)
target_compile_features(AudioVisualizer PUBLIC cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET AudioVisualizer
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:AudioVisualizer>
        VERBATIM)
endif()

install(TARGETS AudioVisualizer)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/music DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/Debug/)