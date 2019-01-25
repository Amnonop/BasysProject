#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "commons.h"
#include "btn.h"
#include "io_registers_handler.h"

unsigned char currentButtonUpState;

void __ISR(_TIMER_5_VECTOR, ipl2) _Timer5Handler(void) 
{
    unsigned char buttonValue;
    if (!btnState.BTNU)
    {
        buttonValue = BTN_GetValue(BUTTON_UP);
        if (currentButtonUpState && !buttonValue) 
        {
            btnState.BTNU = 1;
            currentButtonUpState = buttonValue;
        } 
        else 
        {
            currentButtonUpState = buttonValue;
        }
    }

    if (!BTN_GetValue(1) && !btnState.BTNL)  
    {
        btnState.BTNL = btnState.prevBTNL ;
    }

    if (BTN_GetValue(2)) 
    {
        updateButtonCenterRegister();
    }

    if (!BTN_GetValue(3) && !btnState.BTNR) 
    {
        btnState.BTNR = btnState.prevBTNR ;    
    }

    if (BTN_GetValue(4)) 
    {
        updateButtonDownRegister();
    }
    btnState.prevBTNU = BTN_GetValue(0);
    btnState.prevBTNL = BTN_GetValue(1);
    btnState.prevBTNR = BTN_GetValue(3);

    IFS0bits.T5IF = 0; // clear interrupt flag
}

// Timer period in seconds
#define TMR_TIME    0.0003 // 300 us for each tick

void timer5Setup() {
    PR5 = (int) (((float) (TMR_TIME * PB_FRQ) / 256) + 0.5); //set period register, generates one interrupt every 300 us                     //             set period register, generates one interrupt every 300 us
    TMR5 = 0; //    initialize count to 0
    T5CONbits.TCKPS = 3; //    1:256 prescaler value
    T5CONbits.TGATE = 0; //    not gated input (the default)
    T5CONbits.TCS = 0; //    PCBLK input (the default)
    IPC5bits.T5IP = 2; //    INT step 4: priority
    IPC5bits.T5IS = 0; //    subpriority
    IFS0bits.T5IF = 0; //    clear interrupt flag
    IEC0bits.T5IE = 1; //    enable interrupt
    T5CONbits.ON = 1; //    turn on Timer5
    //macro_enable_interrupts(); //    enable interrupts at CPU
}

void buttonStateHandlerInit() 
{
    btnState.BTNU = 0;
    btnState.BTNL = 0;
    btnState.BTNC = 0;
    btnState.BTNR = 0;
    btnState.BTND = 0;
    currentButtonUpState = 0;
    
    timer5Setup();
}

void resetButtonsState() {
    //btnState.BTNU = 0;
    btnState.BTNL = 0;
    btnState.BTNC = 0;
    btnState.BTNR = 0;
    btnState.BTND = 0;
}
