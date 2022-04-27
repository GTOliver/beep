#include "BeepSynth.h"

#include "oscillators/SineOscillator.h"
#include "voices/OscillatorVoice.h"

#include <algorithm>

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
                        BeepMessage* beep_messages, int n_messages, BeepTime buffer_start_time)
{
    // Clear the output buffer
    for (ulong i = 0; i < buffer_size; ++i) {
        output_buffer[i] = 0.0f;
    }

    auto buffer_duration = static_cast<double>(buffer_size) / static_cast<double>(sample_rate_);

    int current_position = 0;

    for (int i = 0; i < n_messages; ++i) {
        auto fraction = (beep_messages[i].timestamp - buffer_start_time) / buffer_duration;

        // This should never do anything
        fraction = std::clamp(fraction, 0.0, 1.0);

        int message_sample_index = static_cast<int>(fraction * static_cast<double>(buffer_size - 1));

        // Process up to sample with beepc in it
        process(output_buffer + current_position, message_sample_index - current_position);
        beep(beep_messages[i]);
    }
    process(output_buffer + current_position, buffer_size - current_position);
}

void BeepSynth::beep(BeepMessage beep)
{
    voice_->beep(beep);
}

void BeepSynth::process(float* output_buffer, ulong buffer_size)
{
    voice_->process(output_buffer, buffer_size);
}

} // namespace bb
