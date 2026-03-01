cmake_minimum_required(VERSION 3.31)

project(evalx)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE DEBUG)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(evalx src/main.c)

target_include_directories(evalx PUBLIC include)
