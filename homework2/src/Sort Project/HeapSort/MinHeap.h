// MinHeap.h
#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <stdexcept>
#include "MinPQ.h"

template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

    void Swim(int i) {
        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void Sink(int i) {
        int n = heap.size();
        while (2 * i + 1 < n) {
            int j = 2 * i + 1;
            if (j + 1 < n && heap[j + 1] < heap[j]) j++;
            if (heap[i] <= heap[j]) break;
            std::swap(heap[i], heap[j]);
            i = j;
        }
    }

public:
    MinHeap() {}

    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty()) throw std::underflow_error("Empty MinHeap");
        return heap[0];
    }

    void Push(const T& value) override {
        heap.push_back(value);
        Swim(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw std::underflow_error("Empty MinHeap");
        std::swap(heap[0], heap.back());
        heap.pop_back();
        if (!IsEmpty()) Sink(0);
    }
};

#endif#pragma once
