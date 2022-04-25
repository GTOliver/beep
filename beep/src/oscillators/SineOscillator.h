#pragma once

#include "../Common.h"
#include "Oscillator.h"

namespace bb
{

class SineOscillator: public Oscillator
{
public:
    explicit SineOscillator(float frequency, ulong sample_rate);

    void process(float* buffer, ulong buffer_size) override;

    void reset() override;

private:
    float phase_change_per_sample_;
    float phase_;
};

} // namespace bb
