cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

# set project name
project(OpenGLSandbox)

# add opengl
find_package(OpenGL REQUIRED)
add_subdirectory(${CMAKE_SOURCE_DIR}/include/glfw-3.3.2)
include_directories(${CMAKE_SOURCE_DIR}/include/glfw-3.3.2/include)

# add assimp
add_subdirectory(${CMAKE_SOURCE_DIR}/include/assimp-4.0.1)
include_directories(${CMAKE_SOURCE_DIR}/include/assimp-4.0.1/include)

# add freetype
add_subdirectory(${CMAKE_SOURCE_DIR}/include/freetype-2.10.0)
include_directories(${CMAKE_SOURCE_DIR}/include/freetype-2.10.0/include)

# glad
add_library("glad" "${CMAKE_SOURCE_DIR}/include/glad/src/glad.c")

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# created exe using variables
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include" # I moved include files to this directory
)

# set libraries
set(LIBS glfw glad assimp freetype ${CMAKE_DL_LIBS})

# link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS} glfw ${GLFW_LIBRARIES})