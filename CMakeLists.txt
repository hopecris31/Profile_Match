cmake_minimum_required(VERSION 3.23)
PROJECT(untitled2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(untitled2 app.cpp Profile.cpp Profile.h)

target_link_libraries(untitled2 ${PYTHON_LIBRARIES})

add_custom_command(TARGET untitled2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/PythonMapAPIFunctions.py
        ${CMAKE_CURRENT_BINARY_DIR}/PythonMapAPIFunctions.py)

