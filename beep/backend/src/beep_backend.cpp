#include "beep_backend.h"

#include <exception>
#include "Beeper.h"

void beep_init()
{
    try {
        bb::Beeper::instance().start();
    } catch (const std::exception& exc) {
        // TODO: Figure out error-reporting
    }
}

void beep_terminate()
{
    try {
        bb::Beeper::instance().stop();
    } catch (const std::exception& exc) {
        // TODO: Figure out error-reporting
    }
}

void beep_beep()
{
    try {
        bb::Beeper::instance().beep();
    } catch (const std::exception& exc) {
        // TODO: Figure out error-reporting
    }
}
