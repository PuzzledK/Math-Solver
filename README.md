# Calculator

## Requirements
- C++ compiler (e.g., g++, clang++)
- CMake (version 3.0 or higher recommended)

## Build Instructions
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

## How to Run
From the `build/` directory, run:

```sh
./calc
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
