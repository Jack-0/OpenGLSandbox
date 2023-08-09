cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

# ignore deprecated on macos -_-
IF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_SYSTEM_PROCESSOR arm)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
	set_source_files_properties(${sources} PROPERTIES COMPILE_FLAGS
		"-xobjective-c -Wno-deprecated-declarations")
	set_source_files_properties(${sources} PROPERTIES LANGUAGE C)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-w")
ENDIF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")

# set project name
project(OpenGLSandbox)

# add opengl
find_package(OpenGL REQUIRED)
add_subdirectory(${CMAKE_SOURCE_DIR}/include/glfw-3.3.2)
include_directories(${CMAKE_SOURCE_DIR}/include/glfw-3.3.2/include)

# add assimp
# add_subdirectory(${CMAKE_SOURCE_DIR}/include/assimp-5.2.5) # m1 mac
# include_directories(${CMAKE_SOURCE_DIR}/include/assimp-5.2.5/include) # m1 mac
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
IF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
	target_link_libraries(${PROJECT_NAME} "-framework IOKit")
	target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})
ENDIF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
target_link_libraries(${PROJECT_NAME} ${LIBS} glfw ${GLFW_LIBRARIES})
