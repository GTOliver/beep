#include "beep_backend.h"

#include "Beeper.h"

void beep_init()
{
    bb::Beeper::instance().start();
}

void beep_terminate()
{
    bb::Beeper::instance().stop();
}

void beep_beep()
{
    bb::Beeper::instance().beep();
}
