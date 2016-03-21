cmake_minimum_required(VERSION 3.0)

project(test)

add_executable(test1 test1.cc)
target_link_libraries(test1 fltk)

