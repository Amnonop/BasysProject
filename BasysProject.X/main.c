//#include <stdio.h>
//#include "commons.h"
//#include "command_line_arguments.h"
#include "simulator.h"

//
///*
//** Summary: 
//**		Main entry point to the program. It takes a memin.txt file as input 
//**		and simulates the fetch-decode-execute loop of a processor to execute the 
//**		input program.
//** Parameters:
//**		argc - number of command line arguments passed
//**		argv - an array containing the command line arguments passed
//*/
//int main(int argc, char *argv[])
//{
//	checkCommandLineArguments(argc);
//	runSimulator(argv);
//}

/* 
 * File:   main.c
 * Author: Monica Ignat
 *
 * Created on March 31, 2017
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#include "lcd.h"
#include "ssd.h"
#include "btn.h"
#include "swt.h"


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

/***	SSDDemo
**
**	Parameters:
**		
**
**	Return Value:
**		
**
**	Description:
**		This function initializes the SSD pins and calls specific functions for initializing LCD, BTN and SSD modules.
**      The 4 digits display a counter values and the BTNC button resets the counter
**          
*/

void lcdShowInstructionandPc() //already implemented in "initSimulator"
{
    
}

lcdShowSelectedRegister()
{
    
    char firstLcdLine = "R";
    char secondLcdLine = ""; // will print empty string
    char XXString = "";
    int XX = 0X000;
    if(BTN_GetValue(0)) XX++;
    if (XX>0X1FF) XX = 0X000;
    sprintf(XXString, "%X", XX);
    strcat(firstLcdLine, XXString);
    strcat(firstLcdLine, " = ");
    //strcat(firstLcdLine, register[XX]);
    LCD_WriteStringAtPos(firstLcdLine, 0, 0);
    LCD_WriteStringAtPos(secondLcdLine, 1, 0);

}

void lcdShowInstructionCounter()
{
     char firstLcdLine = "";
     //strcat(firstLcdLine, numberOfInstructions);
     LCD_WriteStringAtPos(firstLcdLine, 0, 0);
     
}

void lcdShowSelectedMemory()
{
    char firstLcdLine = "M";
    char secondLcdLine = "RSP = ";
    char AAAString = "";
    int AAA = 0X000;
    int sw5State = SWT_GetValue(0);
    int sw6State = SWT_GetValue(1);
    int switch56Case = sw5State | (sw6State<<2); 
    switch(switch56Case)
    {
        case 0:
        {
            AAA = 0x000;
            break;
        }
        case 1:
        {
            AAA = 0x100;
            break;
        }
        case 2:
        {
            AAA = 0x1FF;
            break;
        }
        case 3:
        {
            AAA = 0x1FF;
            break;
        }
        if(BTN_GetValue(0)) AAA++;
        if (AAA>0X1FF) AAA = 0X000;
        sprintf(AAAString, "%X", AAA);
		strcat(firstLcdLine, AAAString);
        strcat(firstLcdLine, " = ");
        //strcat(firstLcdLine, memory[AAA]);
        // strcat(secondLcdLine, $SP);
        LCD_WriteStringAtPos(firstLcdLine, 0, 0);
        LCD_WriteStringAtPos(secondLcdLine, 1, 0);
    }
}

void getLcdState()
{
    // **should be checked frequently**//
    int swOState = SWT_GetValue(0);
    int sw1State = SWT_GetValue(1);
    int switch12Case = swOState | (sw1State<<2);
    switch(switch12Case)
    {
        case 0:
        {
            lcdShowInstructionandPc(); //already implemented in "initSimulator"
            break;
        }
        case 1:
        {
            lcdShowSelectedRegister();
            break;
        }
        case 2:
        {
            lcdShowSelectedMemory(); //waiting for MEMROY[AAA] and to $SP
            break;
        }
        case 3:
        {
            lcdShowInstructionCounter();
            break;
        }
    }
    
}

void startSimulator()
{
    unsigned int wCnt = 0, baseCnt = 0;
    LCD_Init(); 
    //SSD_Init();
    BTN_Init();
    LCD_WriteStringAtPos("SSD Demo", 0, 0);
    LCD_WriteStringAtPos("Katya", 1, 0);
    
    initSimulator();
    SSD_Init();

// OPTION 1: POLLING    
// ORIGINAL CODE from SSDDemo Project
// The following loop demonstrates POLLING:
    
/*starts here*/
//    while(1)
//    {
//       if(++baseCnt == 1000000)
//        {
//            //display the counter values on the 4 digits available
//            SSD_WriteDigitsGrouped(wCnt++, 0);
//            baseCnt = 0;        
//            //if button C is pressed, reset the counter
//            if (BTN_GetValue(2))
//            {
//                wCnt=0;
//            }
//        }
//    }
/*ends here*/    
}
