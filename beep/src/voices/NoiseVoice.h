#pragma once

#include <random>

#include "Voice.h"

namespace bb
{

class NoiseVoice: public Voice
{
public:
    NoiseVoice();

    void process(float* buffer, ulong buffer_size) override;

private:
    std::random_device random_device_;
    std::mt19937 random_generator_;
    std::uniform_real_distribution<float> random_dist_;
};

} // namespace bb
