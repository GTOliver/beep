#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum BeepError_
{
    BeepError_NoError = 0,
    BeepError_Error = 1
} BeepError;

BeepError beep_init();

BeepError beep_terminate();

BeepError beep_beep();

BeepError beep_beep_at(float frequency);

const char* beep_get_error_message(BeepError error);

#ifdef __cplusplus
};
#endif
