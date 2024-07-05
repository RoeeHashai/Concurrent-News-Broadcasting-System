#include "UnboundedBuffer.h"

template <typename T>
void UnboundedBuffer<T>::insert(const T& item){
    std::lock_guard<std::mutex> lock(mutex);
    buffer.push(item);
    notEmpty.notify_one();
}

template <typename T>
T UnboundedBuffer<T>::remove(){
    std::unique_lock<std::mutex> lock(mutex);
    notEmpty.wait(lock, [this](){return !buffer.empty();});
    T item = buffer.front();
    buffer.pop();
    return item;
}

template class UnboundedBuffer<std::string>;