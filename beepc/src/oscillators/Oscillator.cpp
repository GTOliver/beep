#include "Oscillator.h"

#include <cmath>

namespace bb
{

void Oscillator::prepare(ulong sample_rate)
{
    sample_rate_ = sample_rate;
    update_phase_change_per_sample();
}

void Oscillator::reset_phase()
{
    phase_ = 0.0f;
}

void Oscillator::set_frequency(float frequency)
{
    frequency_ = frequency;
    update_phase_change_per_sample();
}

void Oscillator::update_phase_change_per_sample()
{
    if (sample_rate_ != 0)
        phase_change_per_sample_ = (2.0f * static_cast<float>(M_PI) * frequency_) / static_cast<float>(sample_rate_);

}

} // namespace bb
