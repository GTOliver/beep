#include "Beeper.h"

#include <iostream>

namespace bb
{

Beeper& Beeper::instance()
{
    static Beeper static_instance;
    return static_instance;
}

Beeper::Beeper()
{
    Pa_Initialize();
}

Beeper::~Beeper()
{
    Pa_Terminate();
}

void Beeper::start()
{
    std::cout << "Starting beep callback\n";
}

void Beeper::stop()
{
    std::cout << "Stopping beep callback\n";
}

void Beeper::beep()
{
    std::cout << "Beep\n";
}

} // namespace bb