cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

# set project name
project(OpenGLSandbox)

IF (WIN32)
	# OpenGL
	find_package(OpenGL REQUIRED)
	add_subdirectory(${CMAKE_SOURCE_DIR}/windows/glfw-3.3.2)
	include_directories(${CMAKE_SOURCE_DIR}windows/glfw-3.3.2/include)
ENDIF()

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# set library directory
set(LIB_DIR ${CMAKE_SOURCE_DIR}/libs)

# created exe using variables
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} src/graphics/Shader.cpp src/graphics/Shader.h include/std_image.h src/graphics/Camera.h)

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include" # I moved include files to this directory
)

# set libraries
set(LIBS glfw glad ${CMAKE_DL_LIBS})
# link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})

IF (WIN32)
	target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
ENDIF()
