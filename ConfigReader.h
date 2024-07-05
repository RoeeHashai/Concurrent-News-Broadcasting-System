#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class ConfigReader
{
private:
    std::string filename;
    std::vector<int> numProducts;
    std::vector<int> producerQueueSizes;
    int coEditorQueueSize;

public:
    ConfigReader(const std::string &filename);
    bool loadConfig();
    int getNumProducers() const;
    int getNumProducts(int producerId) const;
    int getProducerQueueSize(int producerId) const;
    int getCoEditorQueueSize() const;

};
#endif // CONFIGREADER_H