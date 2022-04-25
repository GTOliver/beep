#pragma once

#include "../Common.h"

namespace bb
{

class Voice
{
public:
    virtual ~Voice() = default;

    virtual void process(float* buffer, ulong buffer_size) = 0;

    virtual bool is_playing() = 0;

    virtual void beep() = 0;
};

} // namespace bb

