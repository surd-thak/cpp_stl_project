#include <gtest/gtest.h>
#include "MyVector.h"

// Verifies that push_back correctly adds elements and updates size
TEST(VectorTest, PushBackIncreasesSize) {
    MyVector<int> vec;
    EXPECT_EQ(vec.size(), 0);

    vec.push_back(10);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 10);

    vec.push_back(20);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 20);
}

// Verifies that the vector handles capacity resizing automatically
TEST(VectorTest, HandlesResizing) {
    MyVector<int> vec;
    const int count = 100;
    
    for (int i = 0; i < count; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), count);
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec[count - 1], count - 1);
}

// Verifies that accessing out-of-bounds indices throws an exception
TEST(VectorTest, ThrowsOutOfBounds) {
    MyVector<int> vec;
    vec.push_back(5);
    
    EXPECT_THROW(vec[10], std::out_of_range);
}

// Verifies Deep Copy semantics
// Modifying the copy should not affect the original vector
TEST(VectorTest, CopyConstructorDeepCopy) {
    MyVector<int> original;
    original.push_back(10);
    original.push_back(20);

    MyVector<int> copy = original; // Invokes Copy Constructor

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[0], 10);

    // Modify copy
    copy[0] = 99;

    EXPECT_EQ(copy[0], 99);
    EXPECT_EQ(original[0], 10); // Original must remain unchanged
}

// Verifies Move Semantics
// Original vector should be empty after move
TEST(VectorTest, MoveConstructorTransfersOwnership) {
    MyVector<int> original;
    original.push_back(100);
    original.push_back(200);

    MyVector<int> moved_vec = std::move(original); // Invokes Move Constructor

    EXPECT_EQ(moved_vec.size(), 2);
    EXPECT_EQ(moved_vec[0], 100);

    // Original should be in a valid empty state
    EXPECT_EQ(original.size(), 0); 
}

// Verifies Iterator Traversal (begin/end)
TEST(VectorTest, IteratorTraversal) {
    MyVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    int sum = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(sum, 6);
}

// Verifies that iterators can modify underlying data
TEST(VectorTest, IteratorModification) {
    MyVector<int> vec;
    vec.push_back(10);
    
    auto it = vec.begin();
    *it = 20;

    EXPECT_EQ(vec[0], 20);
}