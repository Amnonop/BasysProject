#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "commons.h"
#include "btn.h"
#include "io_registers_handler.h"

BtnState currentButtonState;

void __ISR(_TIMER_5_VECTOR, ipl2) _Timer5Handler(void) 
{
    unsigned char buttonValue;
    if (!btnState.BTNU)
    {
        buttonValue = BTN_GetValue(BUTTON_UP);
        if (currentButtonState.BTNU && !buttonValue) 
        {
            btnState.BTNU = 1;
        } 
        currentButtonState.BTNU = buttonValue;
    }

    buttonValue = BTN_GetValue(BUTTON_LEFT);
    if (!buttonValue && !btnState.BTNL)  
    {
        btnState.BTNL = currentButtonState.BTNL ;
    }
    currentButtonState.BTNL = buttonValue;
    
    buttonValue = BTN_GetValue(BUTTON_RIGHT);
    if (!buttonValue && !btnState.BTNR) 
    {
        btnState.BTNR = currentButtonState.prevBTNR ;    
    }
    currentButtonState.prevBTNR = buttonValue;

    if (!executionState.isPause)
    {
        buttonValue = BTN_GetValue(BUTTON_CENTER);
        if (currentButtonState.BTNC && !buttonValue) 
        {
            updateButtonCenterRegister();
        }
        currentButtonState.BTNC = buttonValue;
        
        if (BTN_GetValue(BUTTON_DOWN)) 
        {
            updateButtonDownRegister();
        }
    }

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
    
    currentButtonState.BTNU = 0;
    currentButtonState.BTNL = 0;
    currentButtonState.BTNC = 0;
    currentButtonState.BTNR = 0;
    currentButtonState.BTND = 0;
    
    timer5Setup();
}

void resetButtonsState() {
    //btnState.BTNU = 0;
    btnState.BTNL = 0;
    btnState.BTNC = 0;
    btnState.BTNR = 0;
    btnState.BTND = 0;
}
