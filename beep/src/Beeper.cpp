#include <memory>

#include "Beeper.h"
#include "PaException.h"
#include "Common.h"
#include "voices/SineVoice.h"

namespace bb
{

Beeper& Beeper::instance()
{
    static Beeper static_instance;
    return static_instance;
}

Beeper::Beeper()
        : sample_rate_{0},
          audio_stream_{nullptr},
          beep_flag_{},
          gain_(0.1f),
          voice_{nullptr},
          envelope_{nullptr}
{
    // Initialise flag to true
    beep_flag_.test_and_set();
}

void Beeper::prepare(ulong sample_rate, float beep_frequency, float attack, float decay)
{
    sample_rate_ = sample_rate;
    voice_ = std::make_unique<SineVoice>(beep_frequency, sample_rate);

    float sample_duration_ms = 1000.0f / static_cast<float>(sample_rate);

    auto attack_samples = static_cast<ulong>(attack / sample_duration_ms);
    auto decay_samples = static_cast<ulong>(decay / sample_duration_ms);

    envelope_ = std::make_unique<Envelope>(attack_samples, decay_samples);
}

void Beeper::start()
{
    auto err = Pa_Initialize();
    check_pa_error(err);

    err = Pa_OpenDefaultStream(
            &audio_stream_,
            0,
            1,
            paFloat32,
            static_cast<double>(sample_rate_),
            512,
            &Beeper::pa_callback,
            this);
    check_pa_error(err);

    err = Pa_StartStream(audio_stream_);
    check_pa_error(err);
}

void Beeper::stop()
{
    try {
        auto err = Pa_StopStream(audio_stream_);
        check_pa_error(err);
        err = Pa_CloseStream(audio_stream_);
        check_pa_error(err);
    } catch (const PaException& error) {
        terminate();
        throw;
    }
    terminate();
}

void Beeper::terminate()
{
    const auto err = Pa_Terminate();
    check_pa_error(err);
}

void Beeper::beep()
{
    beep_flag_.clear();
}

int Beeper::pa_callback(
        const void* input_buffer,
        void* output_buffer,
        unsigned long frames_per_buffer,
        const PaStreamCallbackTimeInfo* info,
        PaStreamCallbackFlags status_flags,
        void* user_data) noexcept
{
    auto ptr = static_cast<Beeper*>(user_data);
    return ptr->callback(
            input_buffer,
            output_buffer,
            frames_per_buffer,
            info,
            status_flags);
}

int Beeper::callback(
        [[maybe_unused]] const void* input_buffer,
        void* output_buffer,
        bb::ulong frames_per_buffer,
        [[maybe_unused]] const PaStreamCallbackTimeInfo* info,
        [[maybe_unused]] PaStreamCallbackFlags status_flags) noexcept
{
    auto f_output_buffer = static_cast<float*>(output_buffer);

    bool beep_triggered = !beep_flag_.test_and_set();

    if (!beep_triggered && envelope_->is_muted()) {
        muter_.process(f_output_buffer, frames_per_buffer);
    } else {
        voice_->process(f_output_buffer, frames_per_buffer);
        envelope_->process(f_output_buffer, frames_per_buffer, beep_triggered);
        gain_.process(f_output_buffer, frames_per_buffer);
    }

    return 0;
}

} // namespace bb
