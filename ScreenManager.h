#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include <iostream>
#include "BoundedBuffer.h"
class ScreenManager
{
private:
    std::shared_ptr<BoundedBuffer<std::string>> smBuffer;
    int doneCount = 0;
public:
    ScreenManager(std::shared_ptr<BoundedBuffer<std::string>> smBuffer);
    void display();
};
#endif // SCREENMANAGER_H