#include "beep.h"

#include <thread>

using namespace std::chrono_literals;

int main()
{
    BEEP_INIT();
    BEEP();
    std::this_thread::sleep_for(1s);
    BEEP();
    BEEP_TERMINATE();
    return 0;
}
