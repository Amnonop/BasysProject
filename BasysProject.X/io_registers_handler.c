#include "io_registers_handler.h"
#include "commons.h"
#include "led.h"

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

int setLedsRegister(int value)
{
    int writingMask = 0x000000FF;
    IORegisters[LedsRegister] = value & writingMask;
    
    LED_SetGroupValue(IORegisters[LedsRegister]);
}

void setIORegister(int registerIndex, int value)
{
    if (!isReadOnlyRegister(registerIndex)) 
    {
        switch (registerIndex)
        {
            case LedsRegister:
                setLedsRegister(value);
                break;
            default:
                IORegisters[registerIndex] = value;
                break;
        }
    }
}

