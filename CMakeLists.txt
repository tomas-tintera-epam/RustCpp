cmake_minimum_required(VERSION 3.5)
project(TaskManager VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(taskmgr TaskManager.cpp)

# Build C wrapper as a static library
add_library(task_c STATIC task_c.cpp)
target_include_directories(task_c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  target_compile_options(task_c PRIVATE /W4 /permissive-)
else()
  target_compile_options(task_c PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ANSI C example: compile with the C compiler (C89) and link to task_c
add_executable(example_c example_c.c)
set_target_properties(example_c PROPERTIES
  C_STANDARD 90
  C_STANDARD_REQUIRED ON
)
target_include_directories(example_c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(example_c PRIVATE task_c stdc++)
if(NOT MSVC)
  target_compile_options(example_c PRIVATE -Wall)
endif()

if(MSVC)
  target_compile_options(taskmgr PRIVATE /W4 /permissive-)
else()
  target_compile_options(taskmgr PRIVATE -Wall -Wextra -Wpedantic)
endif()

option(BUILD_TESTING "Enable building tests" OFF)
