# create variables with output locations
set(PROTO_GEN_SRC ${CMAKE_CURRENT_BINARY_DIR}/)
file(MAKE_DIRECTORY ${PROTO_GEN_SRC})

set(PROTO_SRC "${PROTO_GEN_SRC}/Service.pb.cc")
set(PROTO_INCLUDE "${PROTO_GEN_SRC}/Service.pb.h")
set(GRPC_SRC "${PROTO_GEN_SRC}/Service.grpc.pb.cc")
set(GRPC_INCLUDE "${PROTO_GEN_SRC}/Service.grpc.pb.h")

# create variable containing proto files
set(PROTO_FILES
  ${CMAKE_CURRENT_LIST_DIR}/Service.proto
)

get_target_property(gRPC_CPP_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin IMPORTED_LOCATION_RELEASE)
# generate grpc services and proto messages from .protofile
# (not generated without reference in add_executable)
add_custom_command(
    OUTPUT ${PROTO_SRC}	${PROTO_INCLUDE}
					 ${GRPC_SRC}  ${GRPC_INCLUDE}
    COMMAND protobuf::protoc
    ARGS --grpc_out "${PROTO_GEN_SRC}"
				 --cpp_out "${PROTO_GEN_SRC}"
				  -I="${CMAKE_CURRENT_LIST_DIR}"
				 --plugin=protoc-gen-grpc="${gRPC_CPP_PLUGIN_EXECUTABLE}"
					"${PROTO_FILES}"
)

add_library(${PROJECT_NAME}Proto SHARED
  ${PROTO_SRC}
  ${GRPC_SRC}
  ${PROTO_INCLUDE}
  ${GRPC_INCLUDE}
)

# set_target_properties(${PROJECT_NAME}Proto
# 	PROPERTIES
# 		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
# )


target_compile_features(${PROJECT_NAME}Proto
  PRIVATE
    cxx_std_17
)

target_link_libraries(${PROJECT_NAME}Proto
  PUBLIC protobuf::libprotobuf
  PUBLIC gRPC::grpc++_reflection
)

target_include_directories(${PROJECT_NAME}Proto
  PUBLIC $<BUILD_INTERFACE:${PROTO_GEN_SRC}>
  PUBLIC $<INSTALL_INTERFACE:include>
)

# ############ INSTALL TARGET ############
set_target_properties(${PROJECT_NAME}Proto PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(DIRECTORY ${PROTO_GEN_SRC}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

install(TARGETS ${PROJECT_NAME}Proto
    EXPORT   ${PROJECT_NAME}Proto-export
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT ${PROJECT_NAME}Proto-export
  FILE ${PROJECT_NAME}ProtoTargets.cmake
  NAMESPACE ${PROJECT_NAME}Proto::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}Proto
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ProtoConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}Proto
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ProtoConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}Proto
)

add_library(${PROJECT_NAME}Proto::${PROJECT_NAME}Proto ALIAS ${PROJECT_NAME}Proto)
