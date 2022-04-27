#include "BeepQueue.h"

#include <vector>

namespace bb
{

BeepQueue::BeepQueue(size_t size)
        : beeps_{size}
{}

void BeepQueue::add_beep(BeepMessage beep)
{
    beeps_.try_emplace(std::move(beep));
}

int BeepQueue::get_beeps(BeepMessage* buffer, BeepTime up_to)
{
    BeepMessage local_msg{};

    int n_written = 0;
    while (true) {
        auto* msg = beeps_.peek();
        if (!msg)
            break;

        if (msg->timestamp > up_to)
            break;

        // This cannot fail as this thread is the single reader
        beeps_.try_dequeue(local_msg);

        *buffer = local_msg;
        ++n_written;
        ++buffer;
    }
    return n_written;
}

size_t BeepQueue::capacity() const
{
    return beeps_.max_capacity();
}

} // namespace bb
