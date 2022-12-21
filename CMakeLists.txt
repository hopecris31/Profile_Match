cmake_minimum_required(VERSION 3.23)
PROJECT(untitled2)

set(CMAKE_CXX_STANDARD 23)

find_package(nlohmann_json 3.7.0 REQUIRED)
find_package(Python3 REQUIRED)

include_directories(${Python3_INCLUDE_DIRS})

add_executable(untitled2 app.cpp Profile.cpp Profile.h Address.cpp Address.h ProfileDistanceFunctions.h)

target_link_libraries(untitled2 ${Python3_LIBRARIES})

