#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <iomanip>
#include "BST.h"

void analyzeHeight() {
    std::cout << "Part (a): Binary Search Tree Height Analysis\n";
    std::cout << "==========================================\n\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> sizes = { 100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };

    std::cout << std::setw(8) << "n"
        << std::setw(10) << "Height"
        << std::setw(12) << "log2(n)"
        << std::setw(15) << "Height/log2(n)" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (int n : sizes) {
        BST tree;
        std::uniform_int_distribution<> dis(1, n * 10); // Generate random numbers

        // Insert n random values
        for (int i = 0; i < n; i++) {
            tree.insert(dis(gen));
        }

        int height = tree.height();
        double log2n = log2(n);
        double ratio = height / log2n;

        std::cout << std::setw(8) << n
            << std::setw(10) << height
            << std::setw(12) << std::fixed << std::setprecision(2) << log2n
            << std::setw(15) << std::setprecision(3) << ratio << std::endl;
    }

    std::cout << "\nObservation: The ratio height/log2(n) should be approximately constant around 2,\n";
    std::cout << "confirming that the average height of a randomly built BST is O(log n).\n";
}

int main() {
    analyzeHeight();
    return 0;
}