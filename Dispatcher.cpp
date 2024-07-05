#include "Dispatcher.h"

Dispatcher::Dispatcher(std::vector<std::shared_ptr<BoundedBuffer<std::string>>> producerBuffers,
                       std::shared_ptr<UnboundedBuffer<std::string>> sportsBuffer,
                       std::shared_ptr<UnboundedBuffer<std::string>> newsBuffer,
                       std::shared_ptr<UnboundedBuffer<std::string>> weatherBuffer)
    : producerBuffers(producerBuffers), sportsBuffer(sportsBuffer), newsBuffer(newsBuffer), weatherBuffer(weatherBuffer)
{
}

void Dispatcher::dispatch()
{
    std::vector<bool> done(producerBuffers.size(), false);
    int numDone = 0;
    size_t index = 0;
    while (numDone < producerBuffers.size())
    {
        if (!done[index])
        {
            if (!producerBuffers[index]->isEmpty())
            {
                std::string msg = producerBuffers[index]->remove();
                if (msg == "DONE")
                {
                    done[index] = true;
                    numDone++;
                }
                else
                {
                    sortNews(msg);
                }
            }
        }
        index = (index + 1) % producerBuffers.size();
    }
    sportsBuffer->insert("DONE");
    newsBuffer->insert("DONE");
    weatherBuffer->insert("DONE");
}

void Dispatcher::sortNews(const std::string &news)
{
    if (news.find("SPORTS") != std::string::npos)
    {
        sportsBuffer->insert(news);
    }
    else if (news.find("WEATHER") != std::string::npos)
    {
        weatherBuffer->insert(news);
    }
    else
    {
        newsBuffer->insert(news);
    }
}