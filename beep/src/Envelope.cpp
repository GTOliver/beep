#include "Envelope.h"

namespace bb
{

Envelope::Envelope(ulong decay)
        : playing_{false},
          envelope_value_{0.0f},
          decay_rate_{1.0f / static_cast<float>(decay)}
{
}

void Envelope::process(float* buffer, ulong buffer_size, bool trigger)
{
    if (trigger) {
        playing_ = true;
        envelope_value_ = 1.0f + decay_rate_;
    }

    if (!playing_) {
        for (ulong i = 0; i < buffer_size; ++i) {
            buffer[i] = 0.0;
        }
    } else {
        for (ulong i = 0; i < buffer_size; ++i) {
            if (!playing_) {
                buffer[i] = 0.0;
            } else {
                envelope_value_ -= decay_rate_;
                buffer[i] *= envelope_value_;
                if (envelope_value_ <= 0.0) {
                    playing_ = false;
                }
            }
        }
    }
}

} // namespace bb
