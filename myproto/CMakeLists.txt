cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(MyProto VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

find_package(gRPC CONFIG REQUIRED)
if (gRPC_FOUND)
  message(STATUS "gRPC version ${gRPC_VERSION}")
else()
  message(FATAL_ERROR "gRPC not found")
endif()

find_package(Protobuf MODULE REQUIRED)
if (Protobuf_FOUND)
  message(STATUS "Protobuf version ${Protobuf_VERSION}")
else()
  message(FATAL_ERROR "Protobuf not found")
endif()

# create variables with output locations
set(PROTO_CODEGEN ${CMAKE_CURRENT_BINARY_DIR}/myproto)
file(MAKE_DIRECTORY ${PROTO_CODEGEN})

# create variable containing proto files
set(PROTO_NAMES
  service
)

foreach(FILE ${PROTO_NAMES})
  list(APPEND GRPC_SRC ${PROTO_CODEGEN}/${FILE}.grpc.pb.cc)
  list(APPEND GRPC_INCLUDE ${PROTO_CODEGEN}/${FILE}.grpc.pb.h)
  list(APPEND PROTO_SRC ${PROTO_CODEGEN}/${FILE}.pb.cc)
  list(APPEND PROTO_INCLUDE ${PROTO_CODEGEN}/${FILE}.pb.h)
  list(APPEND PROTO_FILES ${CMAKE_CURRENT_LIST_DIR}/src/${FILE}.proto)
endforeach(FILE)

get_target_property(gRPC_CPP_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin IMPORTED_LOCATION_RELEASE)
# generate grpc services and proto messages from .protofile
# (not generated without reference in add_executable)
add_custom_command(
    OUTPUT ${PROTO_SRC}	${PROTO_INCLUDE}
					 ${GRPC_SRC}  ${GRPC_INCLUDE}
    COMMAND protobuf::protoc
    ARGS --grpc_out ${PROTO_CODEGEN}
				 --cpp_out ${PROTO_CODEGEN}
				  -I="${CMAKE_CURRENT_LIST_DIR}/src"
				 --plugin=protoc-gen-grpc="${gRPC_CPP_PLUGIN_EXECUTABLE}"
         ${PROTO_FILES}
)

add_library(${PROJECT_NAME} SHARED
  ${PROTO_SRC}
  ${GRPC_SRC}
  ${PROTO_INCLUDE}
  ${GRPC_INCLUDE}
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
)


target_compile_features(${PROJECT_NAME}
  PRIVATE cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC protobuf::libprotobuf
  PUBLIC gRPC::grpc++_reflection
)

target_include_directories(${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${PROTO_CODEGEN}>
  PUBLIC $<INSTALL_INTERFACE:include>
)

# ############ INSTALL TARGET ############
install(DIRECTORY ${PROTO_CODEGEN}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

install(TARGETS ${PROJECT_NAME}
    EXPORT   ${PROJECT_NAME}-export
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT ${PROJECT_NAME}-export
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
