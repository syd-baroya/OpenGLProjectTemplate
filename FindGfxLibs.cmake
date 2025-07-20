cmake_minimum_required(VERSION 3.4)

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

    find_package(glfw3 QUIET)

    if(glfw3_FOUND)

        # Include paths are added automatically by the glfw3 find_package
        target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

    elseif(DEFINED ENV{GLFW_DIR})

        set(GLFW_DIR "$ENV{GLFW_DIR}")
        message(STATUS "GLFW environment variable found. Attempting use...")

        if(NOT EXISTS "${GLFW_DIR}/CMakeLists.txt" AND WIN32)
            _findGLFW3_vsbinary(target) 
        elseif(EXISTS "${GLFW_DIR}/CMakeLists.txt")
            _findGLFW3_sourcepkg(target)
        else()
            message(FATAL_ERROR "GLFW environment variable 'GLFW_DIR' found, but points to a directory which is not a source package containing 'CMakeLists.txt'.")
        endif()

        if(GLFW_LIBRARIES)
            target_include_directories(${target} PUBLIC "${GLFW_DIR}/include")
            target_link_libraries(${target} "${GLFW_LIBRARIES}")
        else()
            message(FATAL_ERROR "Internal Error! GLFW_LIBRARIES variable did not get set! Contact your TA, this is their fault.")
        endif()

    elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/include/GLFW/glfw3.h" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/lib/glfw3.lib")
        message(STATUS "Found GLFW in local dep/ directory.")
        target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dep/include")
        target_link_libraries(${target} "${CMAKE_CURRENT_SOURCE_DIR}/dep/lib/glfw3.lib")

    else()
        message(FATAL_ERROR "glfw3 could not be found through find_package or environment varaible 'GLFW_DIR'! glfw3 must be installed!")
    endif()

endfunction(findGLFW3)

# Find and add GLM using find_package or environment variable 
function(findGLM target)

    find_package(glm QUIET)

    if(NOT glm_FOUND)
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dep/include/glm/glm.hpp")
            message(STATUS "Found GLM in local dep/ directory.")
            target_include_directories(${target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dep/include")
        else()
            message(WARNING "glm could not be found through find_package or environment variable 'GLM_INCLUDE_DIR'! glm must be installed!")
        endif()
    else()
        target_include_directories(${target} PUBLIC ${glm_INCLUDE_DIRS})
    endif()
    
endfunction(findGLM)


#find and add assimp dir using environment variable
function(findAssimp target)

    find_package(assimp QUIET)

    if(DEFINED ENV{ASSIMP_DIR})
        set(ASSIMP_DIR "$ENV{ASSIMP_DIR}")
        message(STATUS "Assimp environment variable found. Attempting use...")

        target_include_directories(${target} PUBLIC "${ASSIMP_DIR}/include")
        target_include_directories(${target} PUBLIC "${ASSIMP_DIR}/build/include")
        target_link_libraries(${target} "/usr/local/Cellar/assimp/5.0.1/lib/libassimp.5.0.0.dylib")
        message(STATUS "${ASSIMP_LIBRARIES}")
    else()
        message(FATAL_ERROR "Assimp could not be found through find_package or environment varaible 'ASSIMP_DIR'! Assimp must be installed!")
    endif()

endfunction(findAssimp)


#find and add freetype dir using environment variable
function(findFreetype target)

    find_package(Freetype QUIET)

    if(DEFINED ENV{FREETYPE_DIR})
        set(FREETYPE_DIR "$ENV{FREETYPE_DIR}")
        message(STATUS "Freetype environment variable found. Attempting use...")

        target_include_directories(${target} PUBLIC "${FREETYPE_DIR}/include")
        target_include_directories(${target} PUBLIC "${FREETYPE_DIR}/build/include")
        target_link_libraries(${target} "${FREETYPE_DIR}/lib/libfreetype.dylib")

        message(STATUS "${FREETYPE_LIBRARIES}")
    else()
        message(FATAL_ERROR "Freetype could not be found through find_package or environment varaible 'FREETYPE_DIR'! Freetype must be installed!")
    endif()
endfunction(findFreetype)


function(findBullet target)
    find_package(bullet)
endfunction(findBullet)
    
