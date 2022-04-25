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

void BeepSynth::prepare(ulong sample_rate, float beep_frequency, float attack, float decay)
{
    sample_rate_ = sample_rate;

    auto oscillator = std::make_unique<SineOscillator>(beep_frequency, sample_rate);

    float sample_duration_ms = 1000.0f / static_cast<float>(sample_rate);

    auto attack_samples = static_cast<ulong>(attack / sample_duration_ms);
    auto decay_samples = static_cast<ulong>(decay / sample_duration_ms);

    auto attack_rate = 1.0f / static_cast<float>(attack_samples);
    auto decay_rate = 1.0f / static_cast<float>(decay_samples);

    voice_ = std::make_unique<OscillatorVoice>(std::move(oscillator), attack_rate, decay_rate);

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
        voice_->beep();

    voice_->process(output_buffer, buffer_size);
}

} // namespace bb
