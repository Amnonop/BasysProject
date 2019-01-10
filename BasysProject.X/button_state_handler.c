#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "btn.h"

// The following defines the time between interrupts
#define BTN_TMR_TIME    0.5 // 0.5 sec for each tick (interrupt every 0.5 sec)

void BTN_refreshAll() {
    btnState.BTNU = BTN_checkIfPressed(0);
    btnState.BTNL = BTN_checkIfPressed(1);
    btnState.BTNC = BTN_checkIfPressed(2);
    btnState.BTNR = BTN_checkIfPressed(3);
    btnState.BTND = BTN_checkIfPressed(4);
}

int BTN_checkIfPressed(int btn) {
    int isNowPressed = 0;
    int bResult = 0;

    isNowPressed = BTN_GetValue(btn);
    while (isNowPressed) {
        bResult = 1;
        isNowPressed = BTN_GetValue(btn);
    }
    return bResult;
}

void __ISR(_TIMER_2_VECTOR, ipl7) Timer5ISR(void)
{
    
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

