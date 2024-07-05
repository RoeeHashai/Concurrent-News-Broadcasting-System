#include "ConfigReader.h"

ConfigReader::ConfigReader(const std::string &filename) : filename(filename), coEditorQueueSize(0)
{
}

bool ConfigReader::loadConfig()
{
    std::ifstream file(this->filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open configuration file." << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line))
    {
        // get the header - the first word in the line
        std::istringstream iss(line);
        std::string header;
        iss >> header;

        // check if the header is a Producer header
        if (header == "PRODUCER")
        {
            int producerId, numProducts, producerQueueSize;
            // get the producer id
            iss >> producerId;
            // get the number of products
            file >> numProducts;
            // move to the next line
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // get the producer queue size
            std::getline(file, line);
            std::istringstream qs(line);
            std::string temp;
            qs >> temp >> temp >> temp >> producerQueueSize;
            // store the values
            this->numProducts.push_back(numProducts);
            this->producerQueueSizes.push_back(producerQueueSize);
        }
        else if (header == "Co-Editor")
        {
            // get the Co-Editor queue size
            std::string temp;
            iss >> temp >> temp >> temp >> this->coEditorQueueSize;
        }
    }
    file.close();
    // this->loaded = true;
    return true;
}
int ConfigReader::getNumProducers() const
{
    return this->numProducts.size();
}
int ConfigReader::getNumProducts(int producerId) const
{
    return this->numProducts[producerId];
}
int ConfigReader::getProducerQueueSize(int producerId) const
{
    return this->producerQueueSizes[producerId];
}
int ConfigReader::getCoEditorQueueSize() const
{
    return this->coEditorQueueSize;
}
