#pragma once

#include "Common.h"
#include "BeepMessage.h"

#include "readerwriterqueue.h"

#include <vector>

namespace mc = moodycamel;

namespace bb
{

class BeepQueue
{
public:
    explicit BeepQueue(size_t size);

    void add_beep(BeepMessage beep);

    // Move beeps in the buffer if their timestamps are below the requested timestamp
    // Returns the number of beeps written to the buffer.
    int get_beeps(BeepMessage* buffer, BeepTime up_to);

    size_t capacity() const;

private:
    mc::ReaderWriterQueue<BeepMessage> beeps_;
};

} // namespace bb
