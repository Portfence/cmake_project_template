# cmake_grpc_example
Contains app and mylibrary. Requires cmake 3.10.2 and gRPC 1.20

## Install library

```bash
$ cd mylibrary
$ cmake . -Bbuild             # Generate Makefile in build directory
$ cmake --build build -- -j8  # Run make from build directory
$ sudo make install -C build  # Run make install from build directory
```

## Run app

```bash
$ cd app
$ cmake . -Bbuild             # Generate Makefile in build directory
$ cmake --build build -- -j8  # Run make from build directory
$ ./build/bin/App             # Run App
```
