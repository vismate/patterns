cmake_minimum_required(VERSION 3.14)
project(state_pattern)

set(CXX_STANDARD_REQUIRED 20)
set(COMPILE_FLAGS -Wall -Wextra -Wunused -Wshadow)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp *.hpp *.h *.c)

add_executable(${PROJECT_NAME} ${SOURCES})