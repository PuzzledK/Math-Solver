cmake_minimum_required(VERSION 3.10)
project(MathSolver)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/AST.cpp
    src/Token.cpp
)

# Executable
add_executable(calc ${SOURCES})
