#include "Producer.h"

Producer::Producer(int id, int numProducts, std::shared_ptr<BoundedBuffer<std::string>> buffer) 
: id(id), numProducts(numProducts), buffer(buffer) {
    newsCount["NEWS"] = 0;
    newsCount["SPORTS"] = 0;
    newsCount["WEATHER"] = 0;
}

std::string Producer::getRandomType() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
    switch (dis(gen)) {
        case 0:
            return "NEWS";
        case 1:
            return "SPORTS";
        case 2:
            return "WEATHER";
    }
    return "NEWS";
}

std::string Producer::generateNewsString(const std::string& type) {
    int count = newsCount[type]++;
    std::string news = "Producer " + std::to_string(id + 1) + " " + type + " " + std::to_string(count);
    return news;
}

void Producer::produce()
{
    for (int i = 0; i < numProducts; ++i) {
        std::string type = getRandomType();
        std::string news = generateNewsString(type);
        buffer->insert(news);
    }
    buffer->insert("DONE");
}
