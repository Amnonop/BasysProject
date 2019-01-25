#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#include "lcd.h"
#include "ssd.h"
#include "btn.h"
#include "swt.h"
#include "led.h"
#include "simulator.h"
#include "io_registers_handler.h"
#include "buttonStateHandler.h"
#include "lcd_handler.h"
#include "commons.h"


#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF      


/* ------------------------------------------------------------ */
/*						Configuration Bits		                */
/* ------------------------------------------------------------ */


// Device Config Bits in  DEVCFG1:	
#pragma config FNOSC =	FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	XT
#pragma config OSCIOFNC =	ON

// The follwing configuration sets the Peripheral Bus frequency (I/O Devices frequency)
// to be: (CPU_FRQ/FPBDIV). In this case 80MHz/2 = 40MHz.
// Therefore we define PB_FRQ to 40MHz (in config.h file)
#pragma config FPBDIV =     DIV_2

// Device Config Bits in  DEVCFG2:	
// original PLL frequency = 8MHz
// The following configuration sets the CPU_FRQ frequency to ((8/2)*20)/1 = 80MHz
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

void startSimulator();

int main() 
{
    startSimulator();   
    return (1);
}

void startSimulator()
{
    LCD_Init(); 
    SWT_Init();
    BTN_Init();
    LED_Init();
    buttonStateHandlerInit();
    initLcdHandler();
    initSimulator();
    SSD_Init();
    
    while(1)
    {
        
    }   
}
