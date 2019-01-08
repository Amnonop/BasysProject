#include "io_registers_handler.h"
#include "commons.h"

int isReadOnlyRegister(int registerIndex)
{
    return ((registerIndex == 0) || (registerIndex == 2) || (registerIndex == 3));
}


