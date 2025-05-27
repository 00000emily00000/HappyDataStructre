// MinPQ.h
#ifndef MINPQ_H
#define MINPQ_H

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}                      // �����Ѻc�禡
    virtual bool IsEmpty() const = 0;        // �O�_����
    virtual const T& Top() const = 0;        // ���̤p�ȡ]min priority�^
    virtual void Push(const T&) = 0;         // ���J
    virtual void Pop() = 0;                  // �����̤p��
};

#endif#pragma once
