#include "SineVoice.h"

#include <cmath>

namespace bb
{

SineVoice::SineVoice(float frequency, ulong sample_rate)
        : phase_change_per_sample_{(2.0f * static_cast<float>(M_PI) * frequency) / static_cast<float>(sample_rate)},
          phase_{0}
{}

void SineVoice::process(float* buffer, ulong buffer_size)
{
    for (ulong i = 0; i < buffer_size; ++i) {
        buffer[i] = std::sin(phase_);
        phase_ += phase_change_per_sample_;
    }

    phase_ = std::fmod(phase_, 2.0f * static_cast<float>(M_PI));
}

} // namespace bb
