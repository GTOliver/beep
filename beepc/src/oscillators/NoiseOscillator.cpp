#include "NoiseOscillator.h"

namespace bb
{
NoiseOscillator::NoiseOscillator()
        : random_device_{},
          random_generator_(random_device_()),
          random_dist_{-1, 1}
{}

void NoiseOscillator::process(float* buffer, ulong buffer_size)
{
    for (ulong i = 0; i < buffer_size; ++i)
        buffer[i] = random_dist_(random_generator_);
}

} // namespace bb
