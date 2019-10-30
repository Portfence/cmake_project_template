#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyLibrary::MyLibrary" for configuration ""
set_property(TARGET MyLibrary::MyLibrary APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MyLibrary::MyLibrary PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libMyLibrary.so"
  IMPORTED_SONAME_NOCONFIG "libMyLibrary.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS MyLibrary::MyLibrary )
list(APPEND _IMPORT_CHECK_FILES_FOR_MyLibrary::MyLibrary "${_IMPORT_PREFIX}/lib/libMyLibrary.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
