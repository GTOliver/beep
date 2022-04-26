#include "BeepSynth.h"

#include "oscillators/SineOscillator.h"
#include "voices/OscillatorVoice.h"

namespace bb
{

BeepSynth::BeepSynth()
        : sample_rate_{0},
          voice_{nullptr}
{
}

void BeepSynth::prepare(ulong sample_rate)
{
    sample_rate_ = sample_rate;

    auto attack_time = 10.0f;
    auto decay_time = 200.0f;

    auto oscillator = std::make_unique<SineOscillator>();
    oscillator->prepare(sample_rate_);

    voice_ = std::make_unique<OscillatorVoice>(std::move(oscillator), attack_time, decay_time);
    voice_->prepare(sample_rate);
}

void BeepSynth::process(float* output_buffer, ulong buffer_size,
                        BeepMessage* beep_messages, int n_messages)
{
    // Clear the output buffer
    for (ulong i = 0; i < buffer_size; ++i) {
        output_buffer[i] = 0.0f;
    }

    bool beep_triggered = n_messages > 0;

    if (beep_triggered)
        voice_->beep(beep_messages[0]);

    voice_->process(output_buffer, buffer_size);
}

} // namespace bb
