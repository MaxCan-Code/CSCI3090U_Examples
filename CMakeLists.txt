

cmake_minimum_required(VERSION 3.0)
project(CSCI-3090)

find_package(OpenGL REQUIRED)

# Compile external-libs dependencies
add_subdirectory(external-libs)

include_directories(
        external-libs/glfw/include/
        external-libs/glm/
        external-libs/glew/include/
        shaders/
        tiny_obj_loader/
)

set(ALL_LIBS ${OPENGL_LIBRARY} glfw GLEW)

# Assignment Two
set(A2 "Assignment-Two")
file(GLOB_RECURSE A2_files
        ${A2}/main.cpp
        shaders/*
        tiny_obj_loader/*
        )

add_executable(A2 ${A2_files})
target_link_libraries(A2 ${ALL_LIBS})

# part1
set(P1 "Assignment-One/part1")
file(GLOB_RECURSE P1_files
        ${P1}/main.cpp
        shaders/*
        tiny_obj_loader/*
        )

add_executable(P1 ${P1_files})
target_link_libraries(P1 ${ALL_LIBS})

# part2
set(P2 "Assignment-One/part2")
file(GLOB_RECURSE P2_files
        ${P2}/main.cpp
        shaders/*
        )

add_executable(P2 ${P2_files})
target_link_libraries(P2 ${ALL_LIBS})
