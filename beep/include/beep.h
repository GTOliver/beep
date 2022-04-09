#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef USE_BEEP_BACKEND
#include "beep_backend.h"
#define BEEP_INIT() beep_init();
#define BEEP() beep_beep();
#define BEEP_TERMINATE() beep_terminate();
#else
#define BEEP_INIT();
#define BEEP();
#define BEEP_TERMINATE();
#endif

#ifdef __cplusplus
};
#endif
