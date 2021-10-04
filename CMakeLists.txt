cmake_minimum_required(VERSION 3.5)
project(P2.2 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(NODE_SOURCE
  Node.hpp)

set(LIST_SOURCE
  LinkedList.hpp)

set(FILEALLOC_SOURCE
  FileAllocManager.hpp FileAllocManager.cpp)
  
set (DRIVER_SOURCE
    FileAllocDriver.cpp)
 
set(TEST_SOURCE
 student_tests.cpp)

set(SOURCE ${LIST_SOURCE} ${NODE_SOURCE} ${FILEALLOC_SOURCE})

add_executable(student-tests catch.hpp student_catch.cpp ${SOURCE} ${TEST_SOURCE})
add_executable(FileAllocDriver ${SOURCE} ${DRIVER_SOURCE})

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
   FileAllocManager.cpp FileAllocDriver.cpp student_tests.cpp
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
