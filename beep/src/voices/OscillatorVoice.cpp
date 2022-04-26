#include "OscillatorVoice.h"

namespace bb
{

OscillatorVoice::OscillatorVoice(std::unique_ptr<Oscillator> oscillator,
                                 float attack_time, float decay_time)
        : state_{State::Off},
          oscillator_(std::move(oscillator)),
          sample_rate_(0),
          attack_time_(attack_time),
          decay_time_(decay_time),
          envelope_value_(0.0f),
          attack_rate_(0.0f),
          decay_rate_(0.0f)
{
}

void OscillatorVoice::prepare(ulong sample_rate)
{
    sample_rate_ = sample_rate;
    recalculate_rates();
}

void OscillatorVoice::process(float* buffer, ulong buffer_size)
{
    if (state_ == State::Off)
        return;

    oscillator_->process(buffer, buffer_size);

    for (ulong i = 0; i < buffer_size; ++i) {
        switch (state_) {
            case State::Off:
                break;
            case State::Attacking:
                envelope_value_ += attack_rate_;
                if (envelope_value_ >= 1.0f) {
                    envelope_value_ = 1.0f;
                    state_ = State::Decaying;
                }
                break;
            case State::Decaying:
                envelope_value_ -= decay_rate_;
                if (envelope_value_ <= 0.0f) {
                    envelope_value_ = 0.0f;
                    state_ = State::Off;
                }
                break;
        }
        buffer[i] *= envelope_value_;
    }
}

bool OscillatorVoice::is_playing()
{
    return state_ != State::Off;
}

void OscillatorVoice::beep(BeepMessage msg)
{
    state_ = State::Attacking;
    oscillator_->set_frequency(msg.frequency);
    oscillator_->reset_phase();
}

void OscillatorVoice::recalculate_rates()
{
    if (sample_rate_ != 0) {
        float sample_duration_ms = 1000.0f / static_cast<float>(sample_rate_);
        float inv_sample_duration_ms = 1.0f / sample_duration_ms;

        auto attack_samples = static_cast<ulong>(attack_time_ * inv_sample_duration_ms);
        auto decay_samples = static_cast<ulong>(decay_time_ * inv_sample_duration_ms);

        attack_rate_ = 1.0f / static_cast<float>(attack_samples);
        decay_rate_ = 1.0f / static_cast<float>(decay_samples);
    }
}

} // namespace bb
