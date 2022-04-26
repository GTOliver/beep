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

    void prepare(ulong sample_rate);

    void process(float* output_buffer, ulong buffer_size,
                 BeepMessage* beep_messages, int n_messages, BeepTime buffer_start_time);

private:
    void process(float* output_buffer, ulong buffer_size);

    void beep(BeepMessage beep);

    ulong sample_rate_;
    std::unique_ptr<Voice> voice_;
};

} // namespace bb
