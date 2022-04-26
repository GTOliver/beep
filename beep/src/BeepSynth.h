#pragma once

#include "Common.h"
#include "BeepMessage.h"

#include "Gain.h"
#include "voices/Voice.h"

#include <memory>

namespace bb
{

class BeepSynth
{
public:
    BeepSynth();

    //void prepare(ulong sample_rate, float beep_frequency, float attack, float decay);

    void prepare(ulong sample_rate);

    void process(float* output_buffer, ulong buffer_size,
                 BeepMessage* beep_messages, int n_messages);

private:
    ulong sample_rate_;
    std::unique_ptr<Voice> voice_;
};

} // namespace bb
