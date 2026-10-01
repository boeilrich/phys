cmake_minimum_required(VERSION 3.21)

project(phys LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/circle.cpp
    src/simulation.cpp
    src/util.cpp
    src/aabb.cpp
)

#===================
# TARGET PROPERTIES
#===================

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF

    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -Werror

        # no optimization + sanitizers for debug build
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

#===============
# DEBUG OPTIONS
#===============

string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    $<$<CONFIG:Debug>:${PROJECT_NAME_UPPER}_DEBUG>
)

find_package(glm REQUIRED)
find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} glm raylib)
