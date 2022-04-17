#pragma once

#include "../Common.h"
#include "Voice.h"

namespace bb
{

class SineVoice: public Voice
{
public:
    explicit SineVoice(float frequency, ulong sample_rate);

    void process(float* buffer, ulong buffer_size) override;

private:
    float phase_change_per_sample_;
    float phase_;
};

} // namespace bb
