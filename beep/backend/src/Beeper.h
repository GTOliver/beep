#pragma once

#include "portaudio.h"

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

};

} // namespace bb
