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

include(CTest)
if(BUILD_TESTING)
  enable_testing()

  # C test for the Task C API
  add_executable(test_task_c tests/test_task_c.c)
  set_target_properties(test_task_c PROPERTIES
    C_STANDARD 90
    C_STANDARD_REQUIRED ON
  )
  target_include_directories(test_task_c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(test_task_c PRIVATE task_c stdc++)
  if(NOT MSVC)
    target_compile_options(test_task_c PRIVATE -Wall)
  endif()
  add_test(NAME task_c_test COMMAND test_task_c)
  
  # External ABI consumer: compile with the C compiler and link the produced static lib
  set(EXTERNAL_CONSUMER_SRC ${CMAKE_SOURCE_DIR}/tests/example_consumer.c)
  set(EXTERNAL_CONSUMER_BIN ${CMAKE_BINARY_DIR}/example_consumer)

  add_custom_command(
    OUTPUT ${EXTERNAL_CONSUMER_BIN}
    COMMAND ${CMAKE_C_COMPILER} -std=c99 -I${CMAKE_SOURCE_DIR}
            ${EXTERNAL_CONSUMER_SRC} ${CMAKE_BINARY_DIR}/libtask_c.a -lstdc++ -o ${EXTERNAL_CONSUMER_BIN}
    DEPENDS task_c
    COMMENT "Building external C consumer linked against libtask_c.a"
    VERBATIM
  )

  add_custom_target(external_abi_consumer ALL DEPENDS ${EXTERNAL_CONSUMER_BIN})
  add_test(NAME abi_consumer_run COMMAND ${EXTERNAL_CONSUMER_BIN})
endif()
