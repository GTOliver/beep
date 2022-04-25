#pragma once

#include "../Common.h"

namespace bb
{

class Oscillator
{
public:
    virtual ~Oscillator() = default;

    virtual void process(float* buffer, ulong buffer_size) = 0;

    virtual void reset() = 0;
};

} // namespace bb
