#include <iostream>
#include <vector>
#include "BST.h"

void demonstrateDelete() {
    std::cout << "Part (b): Delete Function with Time Complexity Analysis\n";
    std::cout << "======================================================\n\n";

    BST tree;

    // Insert some sample values
    std::vector<int> values = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45 };

    std::cout << "Inserting values: ";
    for (int val : values) {
        std::cout << val << " ";
        tree.insert(val);
    }
    std::cout << "\nInitial tree height: " << tree.height() << std::endl;

    // Demonstrate deletion
    std::cout << "\nDeleting key 30 (node with two children)...\n";
    tree.deleteKey(30);
    std::cout << "Tree height after deletion: " << tree.height() << std::endl;

    std::cout << "\nDeleting key 10 (leaf node)...\n";
    tree.deleteKey(10);
    std::cout << "Tree height after deletion: " << tree.height() << std::endl;

    std::cout << "\nDeleting key 25 (node with one child)...\n";
    tree.deleteKey(25);
    std::cout << "Tree height after deletion: " << tree.height() << std::endl;
}

int main() {
    demonstrateDelete();
    return 0;
}