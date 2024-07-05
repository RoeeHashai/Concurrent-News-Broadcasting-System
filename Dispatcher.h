#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include <memory>
#include "BoundedBuffer.h"
#include "UnboundedBuffer.h"

class Dispatcher
{
private:
    std::vector<std::shared_ptr<BoundedBuffer<std::string>>> producerBuffers;
    std::shared_ptr<UnboundedBuffer<std::string>> sportsBuffer;
    std::shared_ptr<UnboundedBuffer<std::string>> newsBuffer;
    std::shared_ptr<UnboundedBuffer<std::string>> weatherBuffer;
    void sortNews(const std::string &news);

public:
    Dispatcher(std::vector<std::shared_ptr<BoundedBuffer<std::string>>> producerBuffers,
               std::shared_ptr<UnboundedBuffer<std::string>> sportsBuffer,
               std::shared_ptr<UnboundedBuffer<std::string>> newsBuffer,
               std::shared_ptr<UnboundedBuffer<std::string>> weatherBuffer);
    void dispatch();
};
#endif