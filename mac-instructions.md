# OpenGL on OSX
This is the original document from the course with additional notes on me using CMake with CLion
## Introduction
This is the most difficult platform to work on for OpenGL. Apple has decided that it will no longer support OpenGL in the future. I believe that they will need to reverse this decision, since they have nothing to replace OpenGL. Unfortunately, for the time being Apple has been trying to make OpenGL harder to use on their computers. The things we need to do to make OpenGL work on OSX changes every year. This document describes what I’ve done to get the first example to run correctly on the current version of OSX as of January 2020.
## Building OpenGL Applications
To start with make sure that Xcode is installed on your computer and that the command line tools have been installed. This is usually the case with Xcode, but I noticed that this didn’t happen automatically on my laptop. I used the following line to produce the executable for the first example:
`clang++ -o ex1 main.cpp Shaders.cpp -framework OpenGL -L/opt/local/lib -lGLEW -lglfw`
You should put this into a Makefile and use something like this to make all your OpenGL applications. Unfortunately, the resulting executable immediately crashes with a segmentation fault. There needs to be a number of changes to the source files.
## Source File Changes
The easiest change to make is to remove the include of `windows.h` from both the `main.cpp` and `Shaders.cpp`, since we are not running on Windows. Next, we need to add the following line at the beginning of `example1.vs` and `example1.fs`:
```cpp
#version 330 core
```
You can use a version greater than 330, I’ve tried 410 since the Nvidia GPU on my laptop supported that. The glsl compiler on OSX is very picky and doesn’t support `gl_FragColor` in fragment shaders. The fragment shader should look like:
```cpp
#version 330 core
/*
* Simple fragment sharder for example one
*/
out vec4 colour;
void main() {
colour = vec4(1.0, 0.0, 0.0, 1.0);
}
```

The main changes are in the main.cpp file. These changes make glfw and glew work properly on OSX. Before the call to `glfxCreateWindow` you need to add the following lines:
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
```
You may need to change the major and minor numbers to 3, but no lower. Before the call to `glewInit` add the following line:
`glewExperimental = GL_TRUE;`
These changes should be sufficient to get the program running. These changes will need to be made in all the OpenGL programs.
## CMake Option
There are some nice CMake OpenGL skeletons that uses GLFW, GLEW and GLM, I recommend checking out the repos below
- https://github.com/andystanton/glfw-skeleton
- https://github.com/Shot511/OpenGLSampleCmake
- https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton

and here’s the CMakeLists I used for my labs https://github.com/MaxCantCode/CSCI-3090/blob/master/CMakeLists.txt

## Linking FreeImage
First I downloaded the **Source distribution** on http://freeimage.sourceforge.net/download.html and followed the instructions on `README.osx`. I linked with the static library `FreeImage/Dist/libfreeimage.a`

After that I ran into a problem like on https://stackoverflow.com/q/22922585 , both the answers worked for me
