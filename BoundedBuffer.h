#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H
#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <iostream>

template <typename T>
class BoundedBuffer {
private:
    std::queue<T> buffer;  
    std::mutex mutex;
    std::condition_variable notFull;
    std::condition_variable notEmpty;
    size_t capacity;

public:
    explicit BoundedBuffer(size_t capacity);
    void insert(const T& item);
    T remove();
    bool isEmpty();

};
#endif