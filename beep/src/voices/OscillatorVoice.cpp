#include "OscillatorVoice.h"

namespace bb
{

OscillatorVoice::OscillatorVoice(std::unique_ptr<Oscillator> oscillator,
                                 float attack_rate, float decay_rate)
        : state_{State::Off},
          oscillator_(std::move(oscillator)),
          envelope_value_(0.0f),
          attack_rate_(attack_rate),
          decay_rate_(decay_rate)
{
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

void OscillatorVoice::beep()
{
    state_ = State::Attacking;
    oscillator_->reset();
}

} // namespace bb
