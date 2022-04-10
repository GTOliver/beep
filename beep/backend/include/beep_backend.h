#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef int beep_error;

typedef enum BeepErrorCode_
{
    BeepError_NoError = 0,
    BeepError_Error = 1
} BeepErrorCode;

beep_error beep_init();

beep_error beep_terminate();

beep_error beep_beep();

const char* beep_get_error_message(beep_error error);

#ifdef __cplusplus
};
#endif
