# **c++_stl_project: Custom C++ Container Library**

This is a lightweight implementation of STL-style containers and algorithms.  
I built this project to demonstrate a deeper understanding of **C++ memory management, template metaprogramming, and data structure internals**.

It’s **not** meant to replace the standard library — only to show how containers like `std::vector` and `std::map` work under the hood using modern **C++17**.

---

# **Key Features**

## **1. Custom Vector (`MyVector`)**
A dynamic array implementation that manually manages memory.

- **RAII Compliant:** Implements the *Rule of 5* (copy/move constructors & assignment, destructor)
- **Move Semantics:** Efficient transfer of ownership without expensive deep copies
- **Iterators:** Custom **Random Access Iterator** compatible with range-based loops and algorithms

---

## **2. Custom Map (`MyMap`)**
An associative container built on a self-balancing **AVL Tree**.

- **Backend:** AVL ensures operations remain **O(log n)** even in worst cases  
- **API:** Supports `operator[]`, `insert`, `contains`, and more  
- **Memory Safety:** Deep copies of nodes & recursive cleanup

---

## **3. Generic Algorithms**
Templated algorithms designed to work with custom iterators.

- **QuickSort:** In-place `MySTL::sort` with minimal memory overhead  
- **Find:** Linear search `MySTL::find` compatible with any iterator-based container  

---

# **Project Structure**

```
c++_stl_project/
├── CMakeLists.txt          # Main build configuration
├── src/
│   └── main.cpp            # Demo / driver code
├── include/
│   ├── MyVector.h          # Vector implementation
│   ├── MyMap.h             # Map wrapper
│   ├── MyAVLTree.h         # AVL Tree logic
│   └── MyAlgorithms.h      # Sort & Find algorithms
└── tests/
    ├── CMakeLists.txt      # Test config
    ├── test_vector.cpp     # Vector unit tests
    └── test_map.cpp        # Map/AVL unit tests
```

---

# **How to Build and Run**

This project uses **CMake** for cross-platform builds.

## **Prerequisites**
- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.14+

---

## **Build Instructions**

### **1. Clone / download the repo**

### **2. Create a build directory**
```bash
mkdir build
cd build
```

### **3. Configure and compile**
```bash
cmake ..
make
```

### **4. Run the demo**
```bash
./c++_stl_project_app
```

---

# **Running Unit Tests**

Uses **Google Test (GTest)**.  
CMake automatically downloads GTest during configuration — nothing to install manually.

After building:

### **Run tests directly (recommended)**
```bash
./tests/unit_tests
```

### **OR use CTest**
```bash
ctest
```

---

# **Design Decisions**

### **Why QuickSort?**
QuickSort is **in-place**, unlike Merge Sort (which requires extra arrays).  
Ideal for memory-constrained environments.

### **Why AVL Tree?**
STL uses Red-Black Trees, but **AVL trees are more strictly balanced**, giving slightly faster lookups at the cost of slower inserts.  
A good trade-off for learning purposes.

---

# **License**
Free to use for educational purposes.
