#pragma once

#include "portaudio.h"
#include <atomic>
#include <random>

namespace bb
{

class Beeper
{
public:
    static Beeper& instance();

    void start();

    void stop();

    void beep();

    Beeper(const Beeper&) = delete;

    Beeper& operator=(const Beeper&) = delete;

private:
    Beeper();

    ~Beeper();

    static int pa_callback(
            const void* input_buffer,
            void* output_buffer,
            unsigned long frames_per_buffer,
            const PaStreamCallbackTimeInfo* info,
            PaStreamCallbackFlags status_flags,
            void* user_data) noexcept;

    int callback(
            const void* input_buffer,
            void* output_buffer,
            unsigned long frames_per_buffer,
            [[maybe_unused]] const PaStreamCallbackTimeInfo* info,
            [[maybe_unused]] PaStreamCallbackFlags status_flags) noexcept;

    PaStream* audio_stream_;

    std::atomic_flag beep_flag_;

    std::mt19937 random_generator_;
    std::uniform_real_distribution<float> random_dist_;
};

} // namespace bb
