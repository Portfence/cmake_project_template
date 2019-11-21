# cmake_grpc_example
CMake build structure experimentation. Contains app and mylibrary. Requires cmake 3.10.2 and gRPC 1.20

## Build and install MyProto
MyProto is dependecy of MyLibrary
```bash
$ cd myproto
$ cmake . -Bbuild             # Generate Makefile in build directory
$ cmake --build build -- -j8  # Run make from build directory
$ sudo make install -C build  # Run make install from build directory
```

## Build and install MyLibrary
MyLibrary is dependecy of App
```bash
$ cd mylibrary
$ cmake . -Bbuild             # Generate Makefile in build directory
$ cmake --build build -- -j8  # Run make from build directory
$ sudo make install -C build  # Run make install from build directory
```

## Run app
App starts a gRPC service server on '0.0.0.0:50051'
```bash
$ cd app
$ cmake . -Bbuild             # Generate Makefile in build directory
$ cmake --build build -- -j8  # Run make from build directory
$ ./build/bin/App             # Run App
```

## Structure
```
repo
 |----app/
 |     |----src/
 |     |     |----CMakeLists.txt
 |     |     |----main.cpp
 |     |----CMakeLists.txt
 |
 |----mylibrary/
 |     |----cmake/
 |     |     |----MyLibraryConfig.cmake
 |     |----include/
 |     |     |----my_class.h
 |     |----src/
 |     |     |----my_class.cpp
 |     |----test/
 |     |     |----my_class.test.cpp
 |     |     |----test_main.cpp
 |     |----CMakeLists.txt
 |
 |----myproto/
 |     |----cmake/
 |     |     |----MyProtoConfig.cmake
 |     |----src/
 |     |     |----service.proto
 |     |----CMakeLists.txt
 |
 |----README.md
 |
```
