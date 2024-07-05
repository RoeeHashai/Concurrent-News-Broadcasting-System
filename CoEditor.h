#ifndef COEDITOR_H
#define COEDITOR_H
#include <chrono>
#include <thread>
#include "UnboundedBuffer.h"
#include "BoundedBuffer.h"

class CoEditor
{
private:
    std::shared_ptr<UnboundedBuffer<std::string>> srcBuffer;
    std::shared_ptr<BoundedBuffer<std::string>> dstBuffer;
public:
    CoEditor(std::shared_ptr<UnboundedBuffer<std::string>> srcBuffer,
             std::shared_ptr<BoundedBuffer<std::string>> dstBuffer);
    void edit();
};
#endif // COEDITOR_H