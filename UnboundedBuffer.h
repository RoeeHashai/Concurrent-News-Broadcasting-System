#ifndef UNBOUNDEDBUFFER_H
#define UNBOUNDEDBUFFER_H
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class UnboundedBuffer
{
private:
    std::queue<T> buffer;
    std::mutex mutex;
    std::condition_variable notEmpty;
public:
    UnboundedBuffer() = default;
    void insert(const T& item);
    T remove();
};
#endif