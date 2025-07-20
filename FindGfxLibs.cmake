cmake_minimum_required(VERSION 3.15)

# findGLFW helper function
function(_findGLFW3_vsbinary target)

    FILE(GLOB GLFW_VC_LIB_DIRS "${GLFW_DIR}/lib-vc*")
    
    if(NOT GLFW_VC_LIB_DIRS)
        message(FATAL_ERROR "GLFW_DIR contains neither a CMakeLists.txt nor pre-compiled libraries for visual studio")
    endif()

    set(GLFW_INCLUDE_DIRS "${GLFW_DIR}/include/")

    function(addMSVCPreCompiled version)
        if(NOT EXISTS "${GLFW_DIR}/lib-vc${version}/glfw3.lib")
        message(FATAL_ERROR "Missing required visual studio pre-compiled library!")
        endif()
        set(GLFW_LIBRARIES "${GLFW_DIR}/lib-vc${version}/glfw3.lib" PARENT_SCOPE)
    endfunction()

    if(MSVC_VERSION GREATER_EQUAL 1920)
        addMSVCPreCompiled("2019")
    elseif(MSVC_VERSION GREATER_EQUAL 1910)
        addMSVCPreCompiled("2017")
    elseif(MSVC_VERSION GREATER_EQUAL 1900)
        addMSVCPreCompiled("2015")
    elseif(MSVC_VERSION LESS 1900)
        message(FATAL_ERROR "Visual Studio version is less than minimum (VS 2015)")
    endif()

    set(GLFW_LIBRARIES ${GLFW_LIBRARIES} PARENT_SCOPE)
    message(STATUS "Set GLFW_LIBRARIES: ${GLFW_LIBRARIES}")

endfunction(_findGLFW3_vsbinary)

# findGLFW helper function
function(_findGLFW3_sourcepkg target)

    option(GLFW_BUILD_EXAMPLES "GLFW_BUILD_EXAMPLES" OFF)
    option(GLFW_BUILD_TESTS "GLFW_BUILD_TESTS" OFF)
    option(GLFW_BUILD_DOCS "GLFW_BUILD_DOCS" OFF)

    if(CMAKE_BUILD_TYPE MATCHES Release)
        add_subdirectory(${GLFW_DIR} ${GLFW_DIR}/release)
    else()
        add_subdirectory(${GLFW_DIR} ${GLFW_DIR}/debug)
    endif()

    set(GLFW_LIBRARIES glfw PARENT_SCOPE)

endfunction(_findGLFW3_sourcepkg)


# Find and add GLFW3 using find_package or environment variable 
function(findGLFW3 target)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/include/GLFW/glfw3.h" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/lib/glfw3.lib")
        message(STATUS "Found GLFW in local dep/ directory.")
        target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dep/include")
        target_link_libraries(${target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dep/lib/glfw3.lib")
    else()
        message(FATAL_ERROR "GLFW not found in local dep/ directory. Please ensure it's present or installed system-wide.")
    endif()

endfunction(findGLFW3)

# Find and add GLM using find_package or environment variable 
function(findGLM target)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/include/glm/glm.hpp")
        message(STATUS "Found GLM in local dep/ directory.")
        target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dep/include")
    else()
        message(FATAL_ERROR "GLM not found in local dep/ directory. Please ensure it's present or installed system-wide.")
    endif()
    
endfunction(findGLM)
