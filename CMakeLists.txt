cmake_minimum_required(VERSION 3.15)

project(HybridMpm)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(ENV{EIGEN3_ROOT_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/third-party/Eigen")

include_directories(third-party/spdlog/include)

add_subdirectory(projects)
add_subdirectory(src)