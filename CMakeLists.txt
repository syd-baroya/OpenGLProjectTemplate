cmake_minimum_required(VERSION 3.15)
include("${CMAKE_SOURCE_DIR}/FindGfxLibs.cmake")
project(OpenGLProjectTemplate)

# Set the default startup project in Visual Studio
set(CMAKE_VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(
    "dep/include"
    "src"
)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/helpers/*.cpp" "src/sceneObjects/*.cpp")

# We don't really need to include header and resource files to build, but it's
# nice to have them show up in IDEs.
file(GLOB_RECURSE HEADERS "src/*.h" "src/helpers/*.h" "src/sceneObjects/*.h" "src/*/*.h")
file(GLOB_RECURSE GLSL_SOURCE_FILES "resources/*.glsl" "resources/*.vert" "resources/*.frag")

# Set the executable.
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS} ${GLSL_SOURCE_FILES} dep/glad.c dep/stb_image.cpp)

set_source_files_properties(dep/stb_image.cpp PROPERTIES LANGUAGE CXX)

# Group GLSL files under a "Resource Files" filter in Visual Studio
source_group("Resource Files" FILES ${GLSL_SOURCE_FILES})

# Group these dependency files into a "Library Files" filter in IDEs
source_group("Library Source Files" FILES "${CMAKE_SOURCE_DIR}/dep/glad.c" "${CMAKE_SOURCE_DIR}/dep/stb_image.cpp")

# Helper function included from FindGfxLibs.cmake
findGLFW3(${CMAKE_PROJECT_NAME})
findGLM(${CMAKE_PROJECT_NAME})

# OS specific options and libraries
if(WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC opengl32.lib)
else()
    message(STATUS "Adding GCC style compiler flags")
    add_compile_options("-Wall" "-pedantic" "-Werror=return-type")
    if(APPLE)
        # Add required frameworks for GLFW.
        find_library(COCOA_FRAMEWORK Cocoa)
        find_library(IOKIT_FRAMEWORK IOKit)
        find_library(COREVIDEO_FRAMEWORK CoreVideo)
        find_library(OPENGL_FRAMEWORK OpenGL)
        target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${COCOA_FRAMEWORK} ${IOKIT_FRAMEWORK} ${COREVIDEO_FRAMEWORK} ${OPENGL_FRAMEWORK})
    else()
        # Assumes linux
                target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC GL dl)
    endif()
endif()

add_compile_options("-ggdb")