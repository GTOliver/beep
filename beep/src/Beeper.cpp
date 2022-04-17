#include <memory>

#include "Beeper.h"
#include "PaException.h"
#include "Common.h"
#include "voices/NoiseVoice.h"
#include "voices/SineVoice.h"

namespace bb
{

Beeper& Beeper::instance()
{
    static Beeper static_instance;
    return static_instance;
}

Beeper::Beeper()
        : beep_flag_{},
          audio_stream_{nullptr},
          gain_(0.1f),
          voice_{std::make_unique<SineVoice>(440, 44100)},
          envelope_{1000}
{
    // Initialise flag to true
    beep_flag_.test_and_set();
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
            44100,
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

    voice_->process(f_output_buffer, frames_per_buffer);

    bool beep_triggered = !beep_flag_.test_and_set();

    envelope_.process(f_output_buffer, frames_per_buffer, beep_triggered);
    gain_.process(f_output_buffer, frames_per_buffer);

    return 0;
}

} // namespace bb
