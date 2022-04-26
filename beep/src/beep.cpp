#include "beep.h"

#include <exception>
#include "Beeper.h"

BeepError beep_init()
{
    bb::Beeper& instance = bb::Beeper::instance();
    instance.prepare(44100);
    try {
        instance.start();
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

BeepError beep_terminate()
{
    try {
        bb::Beeper::instance().stop();
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

BeepError beep_beep()
{
    try {
        bb::Beeper::instance().beep();
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

BeepError beep_beep_at(float freq)
{
    try {
        bb::Beeper::instance().beep_at(freq);
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

const char* beep_get_error_message(BeepError error)
{
    switch (error) {
        case BeepError_NoError:
            return "No Error";
        case BeepError_Error:
            return "Error";
        default:
            return "Unknown Error";
    }
}
