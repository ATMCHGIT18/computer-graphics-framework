cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(CGF_Test VERSION 0.1.0 LANGUAGES CXX C)

find_library(UTIL_LIB NAMES util)

include_directories("./FrameWork/include")

add_executable(test test.cpp)

if(UTIL_LIB)
	target_link_libraries(test PRIVATE ${UTIL_LIB})
else()
	message(FATAL_ERROR "libutil is not found!")
endif()