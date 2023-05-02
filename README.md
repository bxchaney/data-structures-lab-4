# ChaneyBLab4

## Configuration Info

Operating System: Ubuntu 22.04

C++ Compiler: g++ 11.3.0

IDE: Visual Studio Code version 1.75.1 with the most recent version of the C/C++ extension pack.

Build System: CMake 3.22.1

I have included my compiled executable in the top directory of this zip, it will not be overwritten when you build from source using CMake

## How to Build

- Assuming the user has access to a Unix-like system with CMake installed.
- From the zip directory, execute the following commands:

```
mkdir build
cd build
cmake ../src
cmake --build .
cd ..
```

- The compiled executable should now be ready at ./build/Lab3 !

## How to Run

- Once the executable is built we can run the program by calling `./build/Lab4 input.txt` from the command line. `input.txt` will contain a list of the datasets you wish to run sorting algorithms for.
- The program will create an output called `summary.csv` in the same directory the executable is run from.