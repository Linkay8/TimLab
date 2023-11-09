cmake_minimum_required(VERSION 3.0)

project(Calculator)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")	

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CALCULATOR_SRC ${CMAKE_SOURCE_DIR}/src/calculator/tokenize.cpp
                        ${CMAKE_SOURCE_DIR}/src/calculator/calculator.cpp
                        ${CMAKE_SOURCE_DIR}/src/calculator/expressions.cpp
                        ${CMAKE_SOURCE_DIR}/src/calculator/calc_exception.cpp
                        ${CMAKE_SOURCE_DIR}/src/calculator/exception.cpp
                        ${CMAKE_SOURCE_DIR}/src/calculator/functions.cpp
                        ${CMAKE_SOURCE_DIR}/src/calculator/template_functions.cpp
                        ${CMAKE_SOURCE_DIR}/src/calculator/expression_simplifier.cpp
                        )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_libraries(gtest gtest_main pthread)

set_source_files_properties(
    ${CALCULATOR_SRC}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    PROPERTIES
    COMPILE_FLAGS "-w"
)

add_executable(calculator ${CALCULATOR_SRC} ${CMAKE_SOURCE_DIR}/src/main.cpp)
#add_executable(tokenize_test ${CALCULATOR_SRC} ${CMAKE_SOURCE_DIR}/test/tokenize/tokenize_test.cpp)

