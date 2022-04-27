#pragma once

#include <atomic>
#include <vector>

#include "portaudio.h"

#include "BeepSynth.h"
#include "BeepQueue.h"
#include "Common.h"
#include "Gain.h"

namespace bb
{

class Beeper
{
public:
    static Beeper& instance();

    void prepare(ulong sample_rate);

    void start();

    void stop();

    void beep();

    void beep_at(float frequency);

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

    PaTime padding_;

    BeepQueue beep_collector_;
    std::vector<BeepMessage> beep_buffer_;
    BeepSynth synth_;
    Gain gain_;

};

} // namespace bb
