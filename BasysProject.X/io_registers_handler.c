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

int setSsdRegister(int value)
{
    IORegisters[SSDRegister] = value;
    SSD_WriteDigitsGrouped(IORegisters[SSDRegister], 4);
}

void updateButtonDownRegister()
{
    IORegisters[BtnDRegister] = IORegisters[BtnDRegister] + 1;
}

void updateButtonCenterRegister()
{
    IORegisters[BtnCRegister] = IORegisters[BtnCRegister] + 1;
}

void updateButtonRegisters()
{
    IORegisters[BtnCRegister] = btnState.BTNC;
    IORegisters[BtnDRegister] = btnState.BTND;
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
            case SSDRegister:
                setSsdRegister(value);
                break;
            default:
                IORegisters[registerIndex] = value;
                break;
        }
    }
}

