#pragma once

#include "../Common.h"
#include "Oscillator.h"

namespace bb
{

class SineOscillator: public Oscillator
{
public:
    void process(float* buffer, ulong buffer_size) override;
};

} // namespace bb
