#include "SineOscillator.h"

#include <cmath>

namespace bb
{

void SineOscillator::process(float* buffer, ulong buffer_size)
{
    for (ulong i = 0; i < buffer_size; ++i) {
        buffer[i] = std::sin(phase_);
        phase_ += phase_change_per_sample_;
    }

    phase_ = std::fmod(phase_, 2.0f * static_cast<float>(B_PI));
}

} // namespace bb
