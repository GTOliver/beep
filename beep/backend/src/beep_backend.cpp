#include "beep_backend.h"

#include <iostream>

namespace bb
{

void init()
{
    std::cout << "BEEP: Init\n";
}

void terminate()
{
    std::cout << "BEEP: Terminate\n";
}

void beep()
{
    std::cout << "beep\n";
}

} // namespace bb
