#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyLibraryProto::MyLibraryProto" for configuration ""
set_property(TARGET MyLibraryProto::MyLibraryProto APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MyLibraryProto::MyLibraryProto PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libMyLibraryProto.so"
  IMPORTED_SONAME_NOCONFIG "libMyLibraryProto.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS MyLibraryProto::MyLibraryProto )
list(APPEND _IMPORT_CHECK_FILES_FOR_MyLibraryProto::MyLibraryProto "${_IMPORT_PREFIX}/lib/libMyLibraryProto.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
