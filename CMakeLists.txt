cmake_minimum_required(VERSION 3.10)

project(LearnCpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

include_directories(include)

add_library(MyLib src/HighPrecision.cpp)
target_link_directories(MyLib PUBLIC include)

add_executable(${PROJECT_NAME} src/Main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE MyLib)