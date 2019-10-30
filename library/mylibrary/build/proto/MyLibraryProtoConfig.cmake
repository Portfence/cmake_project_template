get_filename_component(MyLibraryProto_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
include(CMakeFindDependencyMacro)

set(_TARGET_NAME "MyLibrary")
find_dependency(Protobuf REQUIRED)
find_dependency(gRPC CONFIG REQUIRED)
if(NOT TARGET MyLibraryProto::MyLibraryProto)
  include("${MyLibraryProto_CMAKE_DIR}/${_TARGET_NAME}ProtoTargets.cmake")
endif()
