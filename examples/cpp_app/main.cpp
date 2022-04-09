#include "beep.h"

#include <thread>

void wait()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
}

int main()
{
    BEEP_INIT();
    BEEP();
    wait();
    BEEP();
    wait();
    BEEP_TERMINATE();
    return 0;
}
