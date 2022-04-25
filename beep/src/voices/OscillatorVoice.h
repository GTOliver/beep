#pragma once

#include "Voice.h"
#include "../oscillators/Oscillator.h"

#include <memory>

namespace bb
{

// Voice which uses an oscillator and wraps it in an attack-release envelope
class OscillatorVoice: public Voice
{
public:
    explicit OscillatorVoice(std::unique_ptr<Oscillator> oscillator,
                             float attack_rate, float decay_rate);

    void process(float* buffer, ulong buffer_size) override;

    bool is_playing() override;

    void beep() override;

private:
    enum class State
    {
        Off,
        Attacking,
        Decaying
    };

    State state_;
    std::unique_ptr<Oscillator> oscillator_;

    float envelope_value_;
    float attack_rate_;
    float decay_rate_;
};

} // namespace bb
