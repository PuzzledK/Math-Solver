# Calculator

## Requirements

- C++ compiler (e.g., g++, clang++, MSVC)
- CMake (version 3.0 or higher recommended)

## Build Instructions

### Linux

1. Clone or download the repository.
2. Open a terminal and navigate to the project root directory.
3. Run the following commands:

    ```sh
    mkdir -p build
    cd build
    cmake ..
    make
    ```

This will generate the executable (usually named `calc`) in the `build/` directory.

### Windows (Visual Studio)

1. Clone or download the repository.
2. Open a command prompt (cmd) or PowerShell and navigate to the project root directory.
3. Run the following commands:

    ```sh
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022"    # or use your version of Visual Studio
    cmake --build . --config Release
    ```

This will generate the executable (usually named `calc.exe`) in the `build/Release` directory.

### Windows (MinGW)

1. Clone or download the repository.
2. Open a command prompt (cmd) or PowerShell and navigate to the project root directory.
3. Run the following commands:

    ```sh
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    mingw32-make
    ```

This will generate the executable (usually named `calc.exe`) in the `build/` directory.

## How to Run

- **Linux:** From the `build/` directory, run:
  ```sh
  ./calc
  ```

- **Windows (Visual Studio):** From the `build/Release/` directory, run:
  ```sh
  .\calc.exe
  ```

- **Windows (MinGW):** From the `build/` directory, run:
  ```sh
  .\calc.exe
  ```

## Supported Commands / Functions

The calculator currently supports the following operations and functions:

### Operators

- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`
- Division: `/`
- Exponentiation: `^`
- Parentheses: `(` and `)`

### Functions

- `sin(x)`
- `cos(x)`
- `tan(x)`
- `asin(x)`
- `acos(x)`
- `atan(x)`
- `sqrt(x)`

#### The input and output to Trigonometric functions is in degrees.

### Numbers

- Integer and floating-point numbers (e.g., `42`, `3.14`)

### Example Usage

```
sin(0.5) + cos(0.5)
2^3 + tan(1)
```

If you enter an unknown function or invalid syntax, the program will display an error message.

---

For any issues, please check your compiler and CMake installation, or open an issue in the repository.
