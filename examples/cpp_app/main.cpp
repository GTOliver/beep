#include "beeppp.h"

#include <thread>

template<typename T>
void sleep(std::chrono::duration<T> duration)
{
    std::this_thread::sleep_for(duration);
}

int main()
{
    using namespace std::chrono_literals;
    bpp::ScopedBeeper beeper{};
    bpp::beep();
    sleep(1s);
    bpp::beep();
    sleep(1s);
}
