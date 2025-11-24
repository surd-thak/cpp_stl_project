#include <iostream>
#include <string>
#include "MyVector.h"
#include "MyMap.h"
#include "MyAlgorithms.h"

// Demo struct for generic testing
struct Student {
    int id;
    std::string name;
    double gpa;

    bool operator<(const Student& other) const { return gpa < other.gpa; }
    bool operator==(const Student& other) const { return id == other.id; }
    
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        return os << "ID: " << s.id << " | " << s.name << " (GPA: " << s.gpa << ")";
    }
};

void demoVectorAndAlgorithms() {
    std::cout << "\n=== 1. Vector & Generic Algorithms ===" << std::endl;
    
    MyVector<Student> students;
    students.push_back({101, "Alice", 3.8});
    students.push_back({102, "Bob", 2.5});
    students.push_back({103, "Charlie", 3.9});
    students.push_back({104, "Dave", 3.2});

    std::cout << "[Original]" << std::endl;
    for(auto it = students.begin(); it != students.end(); ++it) std::cout << *it << std::endl;

    // Sort by GPA
    std::cout << "\n[Sorted]" << std::endl;
    MySTL::sort(students.begin(), students.end());
    for(auto it = students.begin(); it != students.end(); ++it) std::cout << *it << std::endl;

    // Find student ID 102
    std::cout << "\n[Search]" << std::endl;
    Student target = {102, "", 0.0};
    auto it = MySTL::find(students.begin(), students.end(), target);
    
    if (it != students.end()) std::cout << "Found: " << *it << std::endl;
    else std::cout << "Not found." << std::endl;
}

void demoMap() {
    std::cout << "\n=== 2. Map (AVL Tree) ===" << std::endl;
    
    MyMap<std::string, int> scores;
    
    scores["Math"] = 90;
    scores["Science"] = 85;
    scores["History"] = 88;
    
    // Update
    scores["Science"] = 95;

    std::cout << "\n[Scores]" << std::endl;
    scores.printAll();

    // Auto-insert default
    std::cout << "\nArt Score (Default): " << scores["Art"] << std::endl;
}

int main() {
    std::cout << "=== c++ stl Demo ===" << std::endl;

    try {
        demoVectorAndAlgorithms();
        demoMap();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}