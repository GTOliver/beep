#include "Envelope.h"

namespace bb
{

Envelope::Envelope(ulong attack, ulong decay)
        : envelope_value_{0.0f},
          state_{State::Off},
          attack_rate_{1.0f / static_cast<float>(attack)},
          decay_rate_{1.0f / static_cast<float>(decay)}
{
}

void Envelope::process(float* buffer, ulong buffer_size, bool trigger)
{
    if (trigger) {
        state_ = State::Attacking;
    }

    if (state_ == State::Off) {
        for (ulong i = 0; i < buffer_size; ++i) {
            buffer[i] = 0.0;
        }
    } else {
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
}

bool Envelope::is_muted()
{
    return state_ == State::Off;
}

} // namespace bb
