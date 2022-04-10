#include "beep.h"

#include <thread>

template<typename T>
void sleep(std::chrono::duration<T> duration)
{
    std::this_thread::sleep_for(duration);
}

int main()
{
    using namespace std::chrono_literals;
    BEEP_INIT();
    BEEP();
    sleep(1s);
    BEEP();
    sleep(1s);
    BEEP_TERMINATE();
}
