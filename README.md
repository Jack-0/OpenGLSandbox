# OpenGL Sandbox
Writing code to learn OpenGL via https://learnopengl.com/.

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

## Problems and solutions

#### Clion (project file is not linking correctly)
1. When building using CLion it maybe necessary to delete cmake-build-debug 
2. Then right click within the project explorer and click reload cmake project
