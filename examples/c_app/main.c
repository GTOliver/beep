#include "beep.h"

#include "unistd.h"


int main()
{
    BEEP_INIT();
    BEEP();
    sleep(1);
    BEEP();
    sleep(1);
    BEEP_TERMINATE();
}
