#pragma once

#include <atomic>
#include <vector>

#include "portaudio.h"

#include "BeepCollector.h"
#include "Common.h"
#include "Envelope.h"
#include "Gain.h"
#include "voices/Voice.h"

namespace bb
{

class Beeper
{
public:
    static Beeper& instance();

    void prepare(ulong sample_rate, float beep_frequency, float attack, float decay);

    void start();

    void stop();

    void beep();

    BeepTime get_now();

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

    ulong sample_rate_;
    PaStream* audio_stream_;

    BeepCollector beep_collector_;
    std::vector<BeepMessage> message_buffer_;

    std::unique_ptr<Voice> voice_;
    Gain gain_;
    Gain muter_{0};
    std::unique_ptr<Envelope> envelope_;
};

} // namespace bb
