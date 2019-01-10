#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "btn.h"
#include "commons.h"
#include "io_registers_handler.h"

// The following defines the time between interrupts
#define BTN_TMR_TIME    0.5 // 0.5 sec for each tick (interrupt every 0.5 sec)

void setButtonCenterState()
{
    int currentButtonState = BTN_GetValue(2);
    if (btnState.BTNC != currentButtonState) 
    {
        btnState.BTNC = currentButtonState;
        updateBtnCRegister();
    }
}

void setButtonDownState()
{
    int currentButtonState = BTN_GetValue(3);
    if (btnState.BTND != currentButtonState) 
    {
        btnState.BTND = currentButtonState;
        updateBtnDRegister();
    }
}

void __ISR(_TIMER_2_VECTOR, ipl7) Timer5ISR(void)
{
    btnState.BTNU = BTN_GetValue(0);
    btnState.BTNL = BTN_GetValue(1);
    setButtonCenterState();
    setButtonDownState();
    btnState.BTNR = BTN_GetValue(3);
    btnState.BTND = BTN_GetValue(4);
}

void timer2Setup() 
{ 
    PR2 = (int) (((float) (BTN_TMR_TIME * PB_FRQ) / 64)); //set period register, generates one interrupt every 2 ms
    TMR2 = 0; //    initialize count to 0
    T2CONbits.TCKPS = 3; //            1:64 prescale value
    T2CONbits.TGATE = 0; //             not gated input (the default)
    T2CONbits.TCS = 0; //             PCBLK input (the default)
    T2CONbits.ON = 1; //             turn on Timer2
    
    IPC2bits.T2IP = 7; //    priority
    IPC2bits.T2IS = 3; //    subpriority
    
    IFS0bits.T2IF = 0; //    clear interrupt flag
    IEC0bits.T2IE = 1; //    enable interrupt
}

void buttonHandlerInit() 
{
    timer2Setup();
}

