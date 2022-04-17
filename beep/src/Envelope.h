#pragma once

#include <optional>

#include "Common.h"

namespace bb
{

class Envelope
{
public:
    Envelope(ulong attack, ulong decay);

    void process(float* buffer, ulong buffer_size, bool trigger);

private:
    enum class State
    {
        Off,
        Attacking,
        Decaying
    };

    float envelope_value_;
    State state_;

    float attack_rate_;
    float decay_rate_;
};

} // namespace bb
