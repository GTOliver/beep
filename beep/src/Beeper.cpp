#include <memory>

#include "Beeper.h"
#include "PaException.h"
#include "Common.h"

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
          beep_collector_{1024},
          message_buffer_{1024},
          gain_{0.1}
{
}

void Beeper::prepare(ulong sample_rate)
{
    sample_rate_ = sample_rate;
    synth_.prepare(sample_rate);
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
    beep_at(880.0f);
}

void Beeper::beep_at(float frequency)
{
    beep_collector_.add_beep(BeepMessage{get_now(), frequency});
}

BeepTime Beeper::get_now()
{
    return Pa_GetStreamTime(audio_stream_);
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
        ulong frames_per_buffer,
        [[maybe_unused]] const PaStreamCallbackTimeInfo* info,
        [[maybe_unused]] PaStreamCallbackFlags status_flags) noexcept
{
    auto f_output_buffer = static_cast<float*>(output_buffer);

    // Collect beep messages from the beep collector
    int n_beeps = 0;
    beep_collector_.get_beeps(message_buffer_.data(), &n_beeps);

    // TODO: Figure out which messages relate to current buffer and
    // TODO: Only send them across to the synth

    // Let the synth fill the output buffer based on the beep messages
    synth_.process(f_output_buffer, frames_per_buffer,
                   message_buffer_.data(), n_beeps);

    // Overall volume adjustment
    gain_.process(f_output_buffer, frames_per_buffer);

    return 0;
}

} // namespace bb
