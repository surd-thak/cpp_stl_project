#include <gtest/gtest.h>
#include "MyMap.h"
#include <string>

// Verifies basic insertion and retrieval using operator[]
TEST(MapTest, InsertAndRetrieve) {
    MyMap<std::string, int> scores;
    scores["Alice"] = 50;
    scores["Bob"] = 30;

    EXPECT_EQ(scores["Alice"], 50);
    EXPECT_EQ(scores["Bob"], 30);
}

// Verifies that assigning to an existing key updates the value
TEST(MapTest, UpdatesExistingKey) {
    MyMap<std::string, int> scores;
    scores["Alice"] = 50;
    scores["Alice"] = 100;

    EXPECT_EQ(scores["Alice"], 100);
}

// Verifies the contains() method for existing and non-existing keys
TEST(MapTest, CheckContains) {
    MyMap<int, int> lookup;
    lookup[1] = 100;

    EXPECT_TRUE(lookup.contains(1));
    EXPECT_FALSE(lookup.contains(999));
}

// Verifies that accessing a non-existent key inserts a default value
TEST(MapTest, AutoCreateOnAccess) {
    MyMap<std::string, int> inventory;
    
    // Key "Apple" does not exist, should insert { "Apple", 0 }
    int count = inventory["Apple"]; 
    
    EXPECT_EQ(count, 0);
    EXPECT_TRUE(inventory.contains("Apple"));
}

// Verifies map behavior with integer keys and string values
TEST(MapTest, IntegerKeyStringValue) {
    MyMap<int, std::string> id_to_name;
    
    id_to_name[101] = "John";
    id_to_name[102] = "Jane";

    EXPECT_EQ(id_to_name[101], "John");
    EXPECT_EQ(id_to_name[102], "Jane");
}

// Verifies that the map handles a large number of insertions
// This indirectly tests the AVL tree balancing logic
TEST(MapTest, LargeScaleInsertion) {
    MyMap<int, int> large_map;
    const int count = 1000;

    for(int i = 0; i < count; ++i) {
        large_map[i] = i * 2;
    }

    // Verify a subset of values
    EXPECT_EQ(large_map[0], 0);
    EXPECT_EQ(large_map[500], 1000);
    EXPECT_EQ(large_map[999], 1998);
}