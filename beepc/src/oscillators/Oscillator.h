#pragma once

#include "../Common.h"
#include "../BeepMessage.h"

namespace bb
{

class Oscillator
{
public:
    virtual ~Oscillator() = default;

    virtual void process(float* buffer, ulong buffer_size) = 0;

    virtual void prepare(ulong sample_rate);

    virtual void reset_phase();

    virtual void set_frequency(float frequency);

protected:
    void update_phase_change_per_sample();

    ulong sample_rate_ = 0;
    float frequency_ = 0.0f;
    float phase_change_per_sample_ = 0.0f;
    float phase_ = 0.0f;
};

} // namespace bb
