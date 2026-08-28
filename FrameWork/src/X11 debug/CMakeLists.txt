cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(CGF_Test VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDART 20)

find_library(UTIL_LIB NAMES util)

include_directories("../../include")

add_executable(test X11_test.cpp)

if(UTIL_LIB)
	target_link_libraries(test PRIVATE ${UTIL_LIB})
else()
	message(FATAL_ERROR "libutil is not found!")
endif()

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    if(X11_FOUND)
        target_link_libraries(test PRIVATE ${X11_LIBRARIES})
    endif()
endif()

if(APPLE)
    target_link_libraries(test PRIVATE 
        "-framework Carbon" 
        "-framework ApplicationServices"
    )
endif()