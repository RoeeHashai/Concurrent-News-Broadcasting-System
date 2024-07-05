#include "ScreenManager.h"

ScreenManager::ScreenManager(std::shared_ptr<BoundedBuffer<std::string>> smBuffer)
    : smBuffer(smBuffer)
{
}

void ScreenManager::display()
{
    while (doneCount < 3)
    {
        std::string msg = smBuffer->remove();
        if (msg == "DONE")
        {
            doneCount++;
            if (doneCount == 3)
            {

                std::cout << "DONE" << std::endl;
            }
        }
        else
        {
            std::cout << msg << std::endl;
        }
    }
}