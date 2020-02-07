

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
)

set(ALL_LIBS ${OPENGL_LIBRARY} glfw GLEW)

# part1
set(P1 "Assignment-One/part1")
file(GLOB_RECURSE P1_files
        ${P1}/*.cpp
        ${P1}/*.cc
        ${P1}/*.h
        shaders/*
        )

add_executable(P1 ${P1_files})
target_link_libraries(P1 ${ALL_LIBS})

# part2
set(P2 "Assignment-One/part2")
file(GLOB_RECURSE P2_files
        ${P2}/*.cpp
        ${P2}/*.cc
        ${P2}/*.h
        shaders/*
        )

add_executable(P2 ${P2_files})
target_link_libraries(P2 ${ALL_LIBS})