cmake_minimum_required(VERSION 3.3)

project(WorldArchitect)

set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

file(GLOB_RECURSE WA_SOURCES src/**/*.cpp)

add_executable(WorldArchitect src/main.cpp ${WA_SOURCES})

target_include_directories(WorldArchitect PUBLIC src)

target_link_libraries(WorldArchitect Threads::Threads lua)
