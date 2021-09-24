cmake_minimum_required(VERSION 3.19)
set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..)


project(FlipIt VERSION 1.0.0)
add_subdirectory(${BASE_DIRECTORY}/../CoreEngine/projects/cmake CoreEngine)
add_executable(FlipIt)


set_target_properties(
    FlipIt PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 20
    DEBUG_POSTFIX _debug
    SUFFIX .elf
    RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/linux_x86_64/
)


target_sources(
    FlipIt PRIVATE
    ${BASE_DIRECTORY}/source/cField.cpp
    ${BASE_DIRECTORY}/source/cGame.cpp
    ${BASE_DIRECTORY}/source/cInterface.cpp
    ${BASE_DIRECTORY}/source/cItem.cpp
    ${BASE_DIRECTORY}/source/cPlayer.cpp
    ${BASE_DIRECTORY}/source/application.cpp
    ${BASE_DIRECTORY}/source/main.cpp
)


target_include_directories(
    FlipIt PRIVATE
    ${BASE_DIRECTORY}/source
)


target_precompile_headers(
   FlipIt PRIVATE
   $<$<COMPILE_LANGUAGE:CXX>: ${BASE_DIRECTORY}/source/main.h>
)


target_link_libraries(
    FlipIt PRIVATE
    CoreEngine
)