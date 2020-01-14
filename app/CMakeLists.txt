cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
project(App LANGUAGES CXX)

# find_package(MyLibrary CONFIG REQUIRED)
find_package(tl-expected CONFIG REQUIRED)

add_subdirectory(src)
