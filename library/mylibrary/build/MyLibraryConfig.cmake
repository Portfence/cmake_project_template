get_filename_component(MyLibrary_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
include(CMakeFindDependencyMacro)

set(_TARGET_NAME "MyLibrary")
find_dependency(Boost REQUIRED COMPONENTS regex)
find_dependency(MyLibraryProto REQUIRED)

if(NOT TARGET MyLibrary::MyLibrary)
  include("${MyLibrary_CMAKE_DIR}/${_TARGET_NAME}Targets.cmake")
endif()
