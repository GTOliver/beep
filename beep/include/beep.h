#pragma once

#ifdef USE_BEEP_BACKEND
#include "beep_backend.h"
#define BEEP_INIT() bb::init();
#define BEEP() bb::beep();
#define BEEP_TERMINATE() bb::terminate();
#else
#define BEEP_INIT();
#define BEEP();
#define BEEP_TERMINATE();
#endif
