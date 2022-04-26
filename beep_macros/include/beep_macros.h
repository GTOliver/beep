#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BEEP_ENABLED

#include "beep.h"

#define BEEP_INIT() beep_init()
#define BEEP_TERMINATE() beep_terminate()
#define BEEP() beep_beep()
#define BEEP_AT(X) beep_beep_at(X)
#define BEEP_GET_ERROR_MESSAGE(X) beep_get_error_message(X)
#else
#define BEEP_INIT() 0
#define BEEP_TERMINATE() 0
#define BEEP() 0
#define BEEP_AT(X) 0
#define BEEP_GET_ERROR_MESSAGE(X) "Beep not enabled"
#endif

#ifdef __cplusplus
};
#endif
