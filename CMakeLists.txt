cmake_minimum_required(VERSION 3.1...3.16)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(yaap LANGUAGES CXX)

add_subdirectory(extern/catch)

add_subdirectory(src)
add_subdirectory(test)
