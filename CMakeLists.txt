cmake_minimum_required(VERSION 3.14)

project(c++_stl_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Helps VS Code IntelliSense

include_directories(include)

# 1. Main Application
add_executable(c++_stl_project_app src/main.cpp)

# ==========================================
# 2. Google Test Integration
# ==========================================
include(FetchContent)

message(STATUS "Fetching GoogleTest... (This may take a moment)")

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Force shared CRT for Windows compatibility (good practice)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Tell CMake to look inside the 'tests' folder now
add_subdirectory(tests)