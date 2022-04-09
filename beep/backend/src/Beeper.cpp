#include "Beeper.h"
#include "PaException.h"


namespace bb
{

Beeper& Beeper::instance()
{
    static Beeper static_instance;
    return static_instance;
}

Beeper::Beeper()
        : random_generator_(),
          random_dist_{-0.5, 0.5},
          beep_flag_(true)
{
    const auto err = Pa_Initialize();
    try {
        check_pa_error(err);
    } catch (const std::exception& error) {
        // TODO: Handle error
    }
}

Beeper::~Beeper()
{
    const auto err = Pa_Terminate();
    try {
        check_pa_error(err);
    } catch (const std::exception& error) {
        // TODO: Handle error
    }
}

void Beeper::start()
{
    auto err = Pa_OpenDefaultStream(
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
    auto err = Pa_StopStream(audio_stream_);
    check_pa_error(err);
    err = Pa_CloseStream(audio_stream_);
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
        unsigned long frames_per_buffer,
        [[maybe_unused]] const PaStreamCallbackTimeInfo* info,
        [[maybe_unused]] PaStreamCallbackFlags status_flags) noexcept
{
    auto f_output_buffer = static_cast<float*>(output_buffer);

    if (beep_flag_.test_and_set()) {
        for (unsigned long i = 0; i < frames_per_buffer; ++i)
            f_output_buffer[i] = 0.0;
    } else {
        for (unsigned long i = 0; i < frames_per_buffer; ++i)
            f_output_buffer[i] = random_dist_(random_generator_);
    }

    return 0;
}

} // namespace bb