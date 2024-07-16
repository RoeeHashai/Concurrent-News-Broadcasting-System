#include "CoEditor.h"

CoEditor::CoEditor(std::shared_ptr<UnboundedBuffer<std::string>> srcBuffer,
                   std::shared_ptr<BoundedBuffer<std::string>> dstBuffer)
    : srcBuffer(srcBuffer), dstBuffer(dstBuffer)
{
}

void CoEditor::edit()
{
    while (true)
    {
        std::string msg = srcBuffer->remove();
        if (msg == "DONE")
        {
            dstBuffer->insert("DONE");
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        dstBuffer->insert(msg);
    }
}