#include "BoundedBuffer.h"

template <typename T>
BoundedBuffer<T>::BoundedBuffer(size_t cap) : capacity(cap) {
    if (capacity == 0) {
        throw std::invalid_argument("Capacity must be greater than 0");
    }
}

template <typename T>
void BoundedBuffer<T>::insert(const T &item) {
    std::unique_lock<std::mutex> lock(mutex);
    notFull.wait(lock, [this]() { return buffer.size() < capacity; });
    buffer.push(item);
    notEmpty.notify_one();
}

template <typename T>
T BoundedBuffer<T>::remove() {
    std::unique_lock<std::mutex> lock(mutex);
    notEmpty.wait(lock, [this]() { return !buffer.empty(); });
    T item = buffer.front();
    buffer.pop();
    notFull.notify_one();
    return item;
}

template <typename T>
bool BoundedBuffer<T>::isEmpty() {
    std::lock_guard<std::mutex> lock(mutex);
    return buffer.empty();
}

template class BoundedBuffer<std::string>;