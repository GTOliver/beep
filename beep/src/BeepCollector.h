#pragma once

#include "Common.h"
#include "BeepMessage.h"

#include "readerwriterqueue.h"

namespace mc = moodycamel;

namespace bb
{

class BeepCollector
{
public:
    explicit BeepCollector(size_t size);

    void add_beep(BeepMessage beep);

    // Move all beeps into the buffer
    // The 'number_written' will be filled with the number of messages written to the buffer.
    // The buffer must be as large as the capacity of this container.
    void get_beeps(BeepMessage* buffer, int* number_written);

    size_t capacity() const;

private:
    mc::ReaderWriterQueue<BeepMessage> beeps_;
};

} // namespace bb
