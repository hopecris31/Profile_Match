cmake_minimum_required(VERSION 3.23)
PROJECT(untitled2)

set(CMAKE_CXX_STANDARD 23)

find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(untitled2 app.cpp Profile.cpp Profile.h Address.cpp Address.h ProfileDistanceFunctions.h)

target_link_libraries(untitled2 ${PYTHON_LIBRARIES})

