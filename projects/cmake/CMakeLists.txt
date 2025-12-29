cmake_minimum_required(VERSION 3.31)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(ENGINE_DIRECTORY ${BASE_DIRECTORY}/../core-engine)

project(FlipIt VERSION 1.0.0)
add_subdirectory(${ENGINE_DIRECTORY}/projects/cmake CoreEngine)
add_executable(FlipIt)

set_target_properties(
    FlipIt PROPERTIES
    C_STANDARD 17
    CXX_STANDARD 23
    CXX_SCAN_FOR_MODULES OFF
    DEBUG_POSTFIX _debug
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH $ORIGIN
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

if(CORE_EMSCRIPTEN)

    set_target_properties(
        FlipIt PROPERTIES
        SUFFIX .html
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/emscripten
    )

else()

    set_target_properties(
        FlipIt PROPERTIES
        SUFFIX .elf
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/linux_x86_64
    )

    if(NOT CORE_DEBUG)

        add_custom_command(
            TARGET FlipIt POST_BUILD
            COMMAND ${ENGINE_DIRECTORY}/tools/scripts/extract_symbols.sh $<TARGET_FILE:FlipIt>
        )

    endif()

endif()