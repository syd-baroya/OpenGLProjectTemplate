cmake_minimum_required(VERSION 3.15)
project(OpenGLProjectTemplate)

# Set the default startup project in Visual Studio
set(CMAKE_VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# vcpkg will handle finding our packages
find_package(assimp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)




# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/helpers/*.cpp" "src/sceneObjects/*.cpp")

# We don't really need to include header and resource files to build, but it's
# nice to have them show up in IDEs.
file(GLOB_RECURSE HEADERS "src/*.h" "src/helpers/*.h" "src/sceneObjects/*.h")
file(GLOB_RECURSE GLSL_SOURCE_FILES "resources/shaders/*.glsl" "resources/shaders/*.vert" "resources/shaders/*.frag")

# Set the executable.
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS} ${GLSL_SOURCE_FILES}
    CMakeLists.txt
    CMakePresets.json
    README.md
    vcpkg.json
)

include_directories(src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ext)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

# Group GLSL files under a "Resource Files" filter in Visual Studio
source_group("Resource Files" FILES ${GLSL_SOURCE_FILES})

# Group build files under 'BuildInfo Files' filter in Visual Studio
source_group("BuildInfo Files" FILES
    CMakeLists.txt
    CMakePresets.json
    README.md
    vcpkg.json
)

# Link libraries found by vcpkg
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    assimp::assimp
    glm::glm
    glfw
    glad::glad
    
)

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
