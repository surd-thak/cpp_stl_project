#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>

template <typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t length;

    // Reallocates memory to a new capacity and moves existing elements
    void realloc(size_t new_capacity) {
        T* new_block = new T[new_capacity];
        
        // Determine number of elements to copy to prevent buffer overflow
        size_t size_to_copy = (length < new_capacity) ? length : new_capacity;
        
        for (size_t i = 0; i < size_to_copy; i++) {
            new_block[i] = std::move(data[i]);
        }

        delete[] data;

        data = new_block;
        capacity = new_capacity;
    }

public:
    // Standard Random Access Iterator implementation
    class Iterator {
    private:
        T* ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        Iterator(T* p) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() { return ptr; }

        Iterator& operator++() { ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        Iterator& operator--() { ptr--; return *this; }
        
        Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
        Iterator operator-(difference_type n) const { return Iterator(ptr - n); }
        difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator<(const Iterator& other) const { return ptr < other.ptr; }
    };

    MyVector() : data(nullptr), capacity(0), length(0) {}

    // Copy Constructor: Performs a deep copy of the source vector
    MyVector(const MyVector& other) : data(nullptr), capacity(0), length(0) {
        realloc(other.capacity);
        for(size_t i=0; i<other.length; ++i) {
            data[i] = other.data[i];
        }
        length = other.length;
    }

    // Move Constructor: Transfers ownership of resources
    MyVector(MyVector&& other) noexcept 
        : data(std::exchange(other.data, nullptr)),
          capacity(std::exchange(other.capacity, 0)),
          length(std::exchange(other.length, 0)) {}

    // Copy Assignment Operator
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            capacity = other.capacity;
            data = new T[capacity];
            for(size_t i=0; i<length; ++i) data[i] = other.data[i];
        }
        return *this;
    }

    // Move Assignment Operator
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = std::exchange(other.data, nullptr);
            capacity = std::exchange(other.capacity, 0);
            length = std::exchange(other.length, 0);
        }
        return *this;
    }

    ~MyVector() {
        delete[] data;
    }

    // Adds an element to the end of the vector, resizing if necessary
    void push_back(const T& value) {
        if (length >= capacity) {
            realloc(capacity == 0 ? 2 : capacity * 2);
        }
        data[length++] = value;
    }

    void push_back(T&& value) {
        if (length >= capacity) {
            realloc(capacity == 0 ? 2 : capacity * 2);
        }
        data[length++] = std::move(value);
    }

    // Access element at index with bounds checking
    T& operator[](size_t index) {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    // Const access for read-only contexts
    const T& operator[](size_t index) const {
        if (index >= length) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    size_t size() const { return length; }
    
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }
};

#endif