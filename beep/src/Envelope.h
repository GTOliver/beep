#pragma once

#include <optional>

#include "Common.h"

namespace bb
{

class Envelope
{
public:
    explicit Envelope(ulong decay);

    void process(float* buffer, ulong buffer_size, bool trigger);

private:
    bool playing_;
    float envelope_value_;

    float decay_rate_;
};

} // namespace bb
