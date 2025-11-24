c++_stl_project: Custom C++ Container Library

This is a lightweight implementation of standard STL-style containers and algorithms. I built this project to demonstrate a deeper understanding of C++ memory management, template metaprogramming, and data structure internals.

It's not meant to replace the standard library, but rather to show how std::vector and std::map work under the hood using modern C++17 standards.

Key Features

1. Custom Vector (MyVector)

A dynamic array implementation that handles memory manually.

RAII Compliant: Implements the "Rule of 5" (Copy Constructor, Move Constructor, Copy Assignment, Move Assignment, Destructor) to prevent memory leaks.

Move Semantics: Efficiently transfers ownership of resources without expensive deep copies.

Iterators: Includes a custom Random Access Iterator, making it compatible with range-based for loops and standard algorithms.

2. Custom Map (MyMap)

An associative container powered by a self-balancing Binary Search Tree.

Backend: Uses an AVL Tree implementation to ensure operations remain $O(\log n)$ even in worst-case scenarios.

API: Supports standard map operations like operator[], insert, and contains.

Memory Safety: Handles deep copying of tree nodes and recursive cleanup.

3. Generic Algorithms

Templated algorithms that work with custom iterators.

QuickSort: An in-place implementation of QuickSort (MySTL::sort) to minimize memory overhead.

Find: A linear search (MySTL::find) for generic containers.

Project Structure

c++_stl_project/
├── CMakeLists.txt          # Main build configuration
├── src/
│   └── main.cpp            # Driver code / Demo
├── include/
│   ├── MyVector.h          # Vector implementation
│   ├── MyMap.h             # Map wrapper
│   ├── MyAVLTree.h         # AVL Tree logic
│   └── MyAlgorithms.h      # Sort & Find functions
└── tests/
    ├── CMakeLists.txt      # Test config
    ├── test_vector.cpp     # Vector unit tests
    └── test_map.cpp        # Map/AVL unit tests


How to Build and Run

I used CMake for the build system to make it cross-platform.

Prerequisites

C++17 compatible compiler (GCC, Clang, or MSVC)

CMake (3.14+)

Building the Project

Clone or download the repo.

Create a build directory:

mkdir build
cd build


Configure and compile:

cmake ..
make


Run the demo:

./c++_stl_project_app


Running Unit Tests

The project uses Google Test (GTest) for validation. CMake will automatically fetch GTest from GitHub when you configure the project, so you don't need to install it manually.

After building (steps above), run:

# Run the test binary directly (recommended for colored output)
./tests/unit_tests

# OR use CTest
ctest


Design Decisions

Why QuickSort? I chose QuickSort for the generic sort algorithm because it's an in-place sort. Unlike Merge Sort, it doesn't require allocating a temporary array, which is better for memory-constrained environments.

Why AVL Tree? While Red-Black trees are common in the actual STL, AVL trees are more strictly balanced. This makes lookups slightly faster at the cost of slower insertions, which seemed like a good trade-off for this simpler implementation.
