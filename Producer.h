#ifndef PRODUCER_H
#define PRODUCER_H
#include <random>
#include <string>
#include <memory>
#include <unordered_map>
#include "BoundedBuffer.h"

class Producer
{
private:
    int id;
    int numProducts;
    std::unordered_map<std::string, int> newsCount;
    std::shared_ptr<BoundedBuffer<std::string>> buffer;
    std::string generateNewsString(const std::string& type);
    std::string getRandomType();

public:
    Producer(int id, int numProducts, std::shared_ptr<BoundedBuffer<std::string>> buffer);
    void produce();
};
#endif