cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)
project(MyLibrary VERSION 1.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(gRPC CONFIG REQUIRED)
if (gRPC_FOUND)
  message(STATUS "gRPC version ${gRPC_VERSION}")
else()
  message(FATAL_ERROR "gRPC not found")
endif()

find_package(Protobuf REQUIRED)
if (Protobuf_FOUND)
  message(STATUS "Protobuf version ${Protobuf_VERSION}")
else()
  message(FATAL_ERROR "Protobuf not found")
endif()

find_package(GTest REQUIRED)
# find_package(Boost COMPONENTS regex REQUIRED)

add_subdirectory(proto)

# ############ CREATE LIB TARGET ############

add_library(${PROJECT_NAME} SHARED
	src/my_class.cpp
)

target_include_directories(${PROJECT_NAME}
	PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	PUBLIC $<INSTALL_INTERFACE:include>
	PRIVATE src
)

target_compile_features(${PROJECT_NAME}
  PRIVATE
    cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
    ${Boost_LIBRARIES}
    MyLibraryProto::MyLibraryProto
		stdc++fs
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# ############ INSTALL TARGET ############
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT ${PROJECT_NAME}-export
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# ############ CREATE TEST TARGET ############

add_executable(test_${PROJECT_NAME}
	test/test_main.cpp
	test/my_class.test.cpp
)

target_compile_features(test_${PROJECT_NAME}
  PRIVATE
    cxx_std_17
)

target_link_libraries(test_${PROJECT_NAME}
	PRIVATE
		${PROJECT_NAME}::${PROJECT_NAME}
		GTest::GTest
)

set_target_properties(test_${PROJECT_NAME}
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
