#include "BeepCollector.h"

#include <vector>

namespace bb
{

BeepCollector::BeepCollector(size_t size)
        : beeps_{size}
{}

void BeepCollector::add_beep(BeepMessage beep)
{
    beeps_.try_emplace(std::move(beep));
}

void BeepCollector::get_beeps(BeepMessage* buffer, int* number_written)
{
    BeepMessage msg{};
    while (beeps_.try_dequeue(msg)) {
        *buffer = msg;
        ++(*number_written);
        ++buffer;
    }
}

size_t BeepCollector::capacity() const
{
    return beeps_.max_capacity();
}

} // namespace bb
