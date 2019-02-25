cmake_minimum_required(VERSION 2.6)

# Name of project
project(FoxEngine)

# Specify project files: header files and source files
file(GLOB SOURCES
    Source/Public/*.h
    Source/Private/*.cpp
)

# Add executable based on the source files
add_executable(FoxEngine ${HDRS} ${SRCS})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(FoxEngine ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH "" CACHE PATH "Folder with GLEW, GLFW, GLM, ASSIMP, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
    find_library(ASSIMP_LIBRARY assimp)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
    find_library(ASSIMP_LIBRARY assimp HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(FoxEngine ${GLEW_LIBRARY})
target_link_libraries(FoxEngine ${GLFW_LIBRARY})
target_link_libraries(FoxEngine ${SOIL_LIBRARY})
target_link_libraries(FoxEngine ${ASSIMP_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(FoxEngine PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
