# Calculator

## Features

- **Basic arithmetic:** Addition (+), Subtraction (-), Multiplication (*), Division (/), Exponentiation (^)
- **Parentheses** for grouping expressions: ( )
- **Constants:**
  - `e` (Euler's number)
- **Functions:**
  - `sin(x)`, `cos(x)`, `tan(x)` (input/output in degrees)
  - `asin(x)`, `acos(x)`, `atan(x)` (output in degrees)
  - `sqrt(x)`
  - `log(x)` (base 10)
  - `ln(x)` (natural log, base e)
- **Variables:**
  - Assignment: `x = 5`
  - Usage: `x + 2`
  - Variable names: alphabets only (e.g., `foo`, `bar`)
- **Blocks:** Use `{ ... }` to group multiple expressions/statements, separated by semicolons.
- **If-Then-Else Expressions:**
  - Syntax: `if(<condition>) then <expr> else <expr>`
  - Supported comparison operators: `==`, `!=`, `>`, `<`, `>=`, `<=`
- **Error handling:**
  - Invalid syntax, division by zero, invalid function input (e.g., sqrt of negative), undeclared variable, unsupported function, etc.

---

# Build Instructions

## Linux

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

## Windows (Visual Studio)

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

## Windows (MinGW)

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

# How to Run

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

# Language Examples

## Arithmetic

```text
2 + 3 * 4
(2 + 3) * 4
2^3 + 1
```

## Functions

```text
sin(30) + cos(60)
sqrt(16)
log(100)
ln(e)
```

## Variables

```text
x = 10
y = sqrt(x)
x + y
```

## Blocks

```text
{
  x = 2;
  y = 3;
  x + y
}
```

## If-Then-Else

```text
if(2 > 1) then 42 else 0
if(x == 10) then x^2 else 0
if(sin(90) == 1) then 1 else 0
```

## Nested Expressions

```text
x = 5
if(x > 3) then sqrt(x^2 + 4) else log(10)
```

## Error Handling

```text
1 / 0           # Division by zero error
sqrt(-1)        # Complex numbers not supported
foo + 1         # Undeclared variable error
```

---

For any issues, please check your compiler and CMake installation, or open an issue in the repository.