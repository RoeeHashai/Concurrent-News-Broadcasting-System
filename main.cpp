#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include "ConfigReader.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include "BoundedBuffer.h"
#include "UnboundedBuffer.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    // Read the configuration file
    ConfigReader config(argv[1]);
    if (!config.loadConfig())
    {
        std::cerr << "Error: Could not load configuration file." << std::endl;
        return 1;
    }

    // Initialize buffers based on configuration
    int numProducers = config.getNumProducers();
    std::vector<std::shared_ptr<BoundedBuffer<std::string>>> producerBuffers(numProducers);
    for (int i = 0; i < numProducers; ++i)
    {
        producerBuffers[i] = std::make_shared<BoundedBuffer<std::string>>(config.getProducerQueueSize(i));
    }

    // Initialize news, sports, weather buffers
    auto sportsBuffer = std::make_shared<UnboundedBuffer<std::string>>();
    auto newsBuffer = std::make_shared<UnboundedBuffer<std::string>>();
    auto weatherBuffer = std::make_shared<UnboundedBuffer<std::string>>();
    auto screenManagerBuffer = std::make_shared<BoundedBuffer<std::string>>(config.getCoEditorQueueSize());

    // Start producer threads
    std::vector<std::thread> threads;
    std::vector<std::shared_ptr<Producer>> producers(numProducers);

    for (int i = 0; i < numProducers; ++i)
    {
        producers[i] = std::make_shared<Producer>(i, config.getNumProducts(i), producerBuffers[i]);
        threads.emplace_back([&producers, i]()
                             { producers[i]->produce(); });
    }

    // Create dispatcher
    Dispatcher dispatcher(producerBuffers, sportsBuffer, newsBuffer, weatherBuffer);

    // Start the dispatcher thread
    threads.emplace_back([&dispatcher]()
                         { dispatcher.dispatch(); });

    // Create co-editor threads
    auto sportsCoEditor = std::make_shared<CoEditor>(sportsBuffer, screenManagerBuffer);
    auto newsCoEditor = std::make_shared<CoEditor>(newsBuffer, screenManagerBuffer);
    auto weatherCoEditor = std::make_shared<CoEditor>(weatherBuffer, screenManagerBuffer);

    // Start the co-editor threads
    threads.emplace_back([&sportsCoEditor]()
                         { sportsCoEditor->edit(); });
    threads.emplace_back([&newsCoEditor]()
                         { newsCoEditor->edit(); });
    threads.emplace_back([&weatherCoEditor]()
                         { weatherCoEditor->edit(); });

    // Create the screen manager
    auto screenManager = std::make_shared<ScreenManager>(screenManagerBuffer);

    // Start the ScreenManager thread
    std::thread screenManagerThread([&screenManager]() {
        screenManager->display();
    });

    // Join all threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Join the ScreenManager thread last
    if (screenManagerThread.joinable()) {
        screenManagerThread.join();
    }

    return 0;
}