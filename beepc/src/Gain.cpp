#include "Gain.h"

namespace bb
{

Gain::Gain(float gain)
        : gain_{gain}
{}

void Gain::process(float* buffer, ulong buffer_size) const
{
    for (ulong i = 0; i < buffer_size; ++i) {
        buffer[i] *= gain_;
    }
}

} // namespace bb
