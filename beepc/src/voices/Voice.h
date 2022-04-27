#pragma once

#include "../Common.h"
#include "../BeepMessage.h"

namespace bb
{

class Voice
{
public:
    virtual ~Voice() = default;

    virtual void prepare(ulong sample_rate) = 0;

    virtual void process(float* buffer, ulong buffer_size) = 0;

    virtual bool is_playing() = 0;

    virtual void beep(BeepMessage msg) = 0;
};

} // namespace bb

