#include <iostream>
#include "MinHeap.h"

int main() {
    MinHeap<int> pq;

    pq.Push(5);
    pq.Push(3);
    pq.Push(8);
    pq.Push(1);

    while (!pq.IsEmpty()) {
        std::cout << pq.Top() << " ";
        pq.Pop();
    }
    std::cout << std::endl;

    return 0;
}