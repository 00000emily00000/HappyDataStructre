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

    std::cout << "\nTime Complexity Analysis:\n";
    std::cout << "========================\n";
    std::cout << "- Best case: O(log n) - when tree is balanced\n";
    std::cout << "- Average case: O(log n) - for randomly built trees\n";
    std::cout << "- Worst case: O(n) - when tree is completely unbalanced (like a linked list)\n";
    std::cout << "\nExplanation:\n";
    std::cout << "The time complexity depends on the height of the tree, as we need to\n";
    std::cout << "traverse from root to the node to be deleted. In a balanced tree, this\n";
    std::cout << "requires O(log n) operations, but in the worst case (degenerate tree),\n";
    std::cout << "it might require O(n) operations.\n";

    std::cout << "\nDeletion Algorithm:\n";
    std::cout << "1. If node has no children: simply remove it\n";
    std::cout << "2. If node has one child: replace node with its child\n";
    std::cout << "3. If node has two children: replace with inorder successor,\n";
    std::cout << "   then delete the successor\n";
}

int main() {
    demonstrateDelete();
    return 0;
}