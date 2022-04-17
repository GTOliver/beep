#pragma once

#include "Common.h"

namespace bb
{

class Gain
{
public:
    explicit Gain(float gain);

    void process(float* buffer, ulong buffer_size) const;

private:
    float gain_;
};

} // namespace bb
