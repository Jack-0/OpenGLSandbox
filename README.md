# OpenGL Sandbox

Writing code to learn OpenGL via https://learnopengl.com/. <br>
The project has now turned into a sort of small game engine. :see_no_evil:

## Description

The code is compiled using cmake.
Code compiles and runs on both Linux and Windows.

## How to install on linux

1. `$ git clone https://github.com/Jack-0/OpenGLSandbox` <br> 
2. `$ cd OpenGLSandbox` <br>
3. `$ mkdir build` <br>
4. `$ cd build` <br>
5. `$ cmake ..` <br>
6. `$ make -j7` <br>
7. `$ ./OpenGLSandbox` <br> 

## Dependencies

- GLFW
- ASSIMP
- GLAD
- GLM
- harfbuzz (macos brew install harfbuzz)

## Problems and solutions :monocle_face:

#### Clion (project file is not linking correctly)

1. When building using CLion it maybe necessary to delete cmake-build-debug 
2. Then right click within the project explorer and click reload cmake project

#### M1 Macos

Builds but hits a segfault, might be due to 5.2.5 assimp usage or arm arch

- edit `CMakeLists.txt` to use assimp-5.2.5
- `cd build`
- `cmake ..`
- `make`
- open debugger `lldb OpenGLSandbox`
- in lldb hit `r` to run
