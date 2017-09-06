cmake_minimum_required(VERSION 3.7)
project(LinkedList)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES mpasswdsort.c mpasswdsort.h list.c list.h)
add_executable(LinkedList ${SOURCE_FILES})