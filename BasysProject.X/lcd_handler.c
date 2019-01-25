#include "commons.h"

int registerNumber;
int currentSwitch12Case;

void initLcdHandler()
{
    registerNumber = 0;
    currentSwitch12Case = 0;
}

void clearLcdDisplay()
{
    //clears lcd display in order to refresh for each interupt
    LCD_WriteStringAtPos("                                    ", 0, 0);
    LCD_WriteStringAtPos("                                      ", 1, 0);
}

void lcdShowInstructionandPc() 
{
    char instructionString[HEX_WORD_LENGTH + 1];
    char pcString[4];
    sprintf(instructionString, "%08X", memory[executionState.pc]);
    LCD_WriteStringAtPos(instructionString, 0, 0);
    sprintf(pcString, "%03X", executionState.pc);
    LCD_WriteStringAtPos(pcString, 1, 0);
}

void lcdShowSelectedRegister()
{
    int registerValue = 0;
    char firstLcdLine[15] = "R";
    char registerNumberString[3] = "";
    char registerValueString[9] = "";
    
    if(btnState.BTNU) 
    {
        btnState.BTNU = 0;
        registerNumber++;
    }
    
    if (registerNumber > NUM_OF_REGISTERS) 
        registerNumber = 0;
    
    sprintf(registerNumberString, "%02X", registerNumber);
    strcat(firstLcdLine, registerNumberString);
    registerValue = registers[registerNumber];
    sprintf(registerValueString, "%08X", registerValue);
    strcat(firstLcdLine, " = ");
    strcat(firstLcdLine,registerValueString);
    LCD_WriteStringAtPos(firstLcdLine, 0, 0);
    LCD_WriteStringAtPos("", 1, 0);
}

void lcdShowSelectedMemory()
{
    char firstLcdLine[] = "M";
    char secondLcdLine[] = "";
    char memoryAdressString[] = "";
    int memoryAdress = 0X000;
    char memoryValueString[] = "";
    int memoryValue = 0;
    int registerSpValue = 0;
    char registerTempSpString[] = "";
    char registerSpString[] = "";
    int sw5State = swtState.SW5;
    int sw6State = swtState.SW6;
    int switch56Case = sw5State + (sw6State*2); 
        
    if  (executionState.lcdState != 2)
        switch(switch56Case)
        {
            case 0:
            {
                memoryAdress = 0x000;
                break;
            }
            case 1:
            {
                memoryAdress = 0x100;
                break;
            }
            case 2:
            {
                memoryAdress = 0x1FF;   
                break;
            }
            case 3:
            {
                memoryAdress = 0x1FF;
                break;
            }
        }
    else
        memoryAdress = executionState.memAdress4lcd;
    
    if(btnState.BTNU)
    {
        memoryAdress++;
        btnState.BTNU = 0;
    }
    
    if (memoryAdress>0x1FF) memoryAdress = 0x000;
    executionState.memAdress4lcd = memoryAdress;
    //resetButtonsState();
    sprintf(memoryAdressString, "%03X", memoryAdress);
    strcat(firstLcdLine, memoryAdressString);
    strcat(firstLcdLine, " = ");
    memoryValue = memory[memoryAdress];
    sprintf(memoryValueString, "%08X", memoryValue);
    strcat(firstLcdLine, memoryValueString);
    registerSpValue = registers[13];
    sprintf(registerTempSpString, "   ");
    sprintf(registerTempSpString, "%03X", registerSpValue);
    
    LCD_WriteStringAtPos(firstLcdLine, 0, 0);
    strcpy(registerSpString, (registerTempSpString));
    strcpy(secondLcdLine,"RSP ="); 
    strcat(secondLcdLine, registerSpString);
    LCD_WriteStringAtPos(secondLcdLine, 1, 0);
}

void lcdShowInstructionCounter()
{
         char instructionCounterString[] = "";
         sprintf(instructionCounterString, "%X", instructionCounter); //return to %X
         LCD_WriteStringAtPos(instructionCounterString, 0, 0);
}

void getLcdState()
{
    // **should be checked frequently**//
    int sw0State = swtState.SW0;
    int sw1State = swtState.SW1;
    int switch12Case = sw0State + (sw1State*2);
    if (currentSwitch12Case != switch12Case)
    {
        currentSwitch12Case = switch12Case;
        clearLcdDisplay();
    }
    switch(switch12Case)
    {
        case 0:
        {
            lcdShowInstructionandPc();
            executionState.lcdState = 0;
            break;
        }
        case 1:
        {
            lcdShowSelectedRegister();
            executionState.lcdState = 1;
            break;
        }
        case 2:
        {
            lcdShowSelectedMemory();
            executionState.lcdState = 2;
            break;
        }
        case 3:
        {
            lcdShowInstructionCounter();
            executionState.lcdState = 3;
            break;
        }
    }
    
}
