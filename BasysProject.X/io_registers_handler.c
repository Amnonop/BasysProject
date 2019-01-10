#include "io_registers_handler.h"
#include "commons.h"

enum IORegisterIndex
{
    CounterRegister = 0,
    LedsRegister = 1,
    BtnCRegister = 2,
    BtnDRegister = 3,
    SSDRegister = 4
};

int isReadOnlyRegister(int registerIndex)
{
    return ((registerIndex == CounterRegister) || 
            (registerIndex == BtnCRegister) || 
            (registerIndex == BtnDRegister));
}

int updateCounterRegister()
{
    if (IORegisters[CounterRegister] == 0xFFFFFFFF) 
    {
        IORegisters[CounterRegister] = 0;
    }
    else
    {
        IORegisters[CounterRegister] = IORegisters[0] + 1;
    }
}


