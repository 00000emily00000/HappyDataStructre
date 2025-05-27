// MinPQ.h
#ifndef MINPQ_H
#define MINPQ_H

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}                      // 虛擬解構函式
    virtual bool IsEmpty() const = 0;        // 是否為空
    virtual const T& Top() const = 0;        // 取最小值（min priority）
    virtual void Push(const T&) = 0;         // 插入
    virtual void Pop() = 0;                  // 移除最小值
};

#endif#pragma once
