cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(App LANGUAGES CXX)

find_package(MyLibrary CONFIG REQUIRED)

add_subdirectory(src)
