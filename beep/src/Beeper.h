#pragma once

#include <atomic>

#include "portaudio.h"

#include "Envelope.h"
#include "Gain.h"
#include "voices/Voice.h"

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

    static void terminate();

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

    std::unique_ptr<Voice> voice_;
    Gain gain_;
    Envelope envelope_;
};

} // namespace bb
