#include "beep.h"

#include <exception>
#include "Beeper.h"

beep_error beep_init()
{
    bb::Beeper& instance = bb::Beeper::instance();
    //instance.prepare(44100, 880, 10, 200);
    instance.prepare(44100);
    try {
        instance.start();
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

beep_error beep_terminate()
{
    try {
        bb::Beeper::instance().stop();
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

beep_error beep_beep()
{
    try {
        bb::Beeper::instance().beep();
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

beep_error beep_beep_at(float freq)
{
    try {
        bb::Beeper::instance().beep_at(freq);
    } catch (const std::exception& exc) {
        return BeepError_Error;
    }
    return BeepError_NoError;
}

const char* beep_get_error_message(beep_error error)
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
