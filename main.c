//  This program will turn on and off LEDs located on the TI Stellaris board
//  using the header file
//  The header file contains the macros for the deferenced pointers to the memory addresses
//  For example...
//  *((unsigned int *)0x400FE608U) is the same as SYSCTL->RCGCGPIO in the header file
//  It is listed in the code for educational purposes and was defined prior to adding the header file
//  by reviewing the lm4f120h5qr datasheet and looking at the memory map, registers
//  The registers are all defined in the datasheet.   
////////////////////////////////////////////////////////////////////////////

#include <lm4f120h5qr.h>

void delay();

int main()
{
  // set RCGCGPIO - Clock Gating control memory address (page 314)
  // Base memory address for RCGCGPIO is 0x400FE000 with offset 0x608
  // *((unsigned int *)0x400FE608U) = 0x20U;  is....
  // pointer to memory address where bit 5 is enabled for GPIO Port F
  SYSCTL->RCGCGPIO |= 0X20;  // same as pointer to memory address above...


  // Set GPIO Data Direction (GPIODIR) (page 622)
  // Used to configure each pin as input or output - 0 = input, 1 = output
  // Base memory address 0x40025000 with offset 0x400
  // LEDs on the board are PF1, PF2 and PF3 or bits 1, 2 and 3 or 0x0E
  // *((unsigned int *)0x40025400U) = 0x0EU;
  GPIOF->DIR |= 0x0E;  // same as pointer to memory address above


  // Set GPIO Digital Enable (GPIODEN) (page 641)
  // Used to enable each pin as input or output - 0 = input, 1 = output
  // Base memory address 0x40025000 with offset 0x51C
  // LEDs on the board are PF1, PF2 and PF3 or bits 1, 2 and 3 or 0x0E
  // *((unsigned int *)0x4002551CU) = 0x0EU;
  GPIOF->DEN |= 0x0E;  // same as pointer to memory address above

   // Set GPIO Data Register - set specific pins - while toggling
  while(1)
  {
     // *((unsigned int *)0x400253FCU) = 0x02U;  // same as below
     GPIOF->DATA = 0x02;  // 0b0010 green off, blue off, red on
     delay();  // counter used to delay between LED ON

     // *((unsigned int *)0x400253FCU) = 0x04U;   // same as below
     GPIOF->DATA = 0x04;  // 0b0100 green off, blue off, red on
     delay();  // counter used to delay between LED ON

     // *((unsigned int *)0x400253FCU) = 0x08U;   // ame as below
     GPIOF->DATA = 0x08;  // 0b1000 green on, blue off, red off
     delay();  // counter used to delay between LED ON
  }

  return 0;
}

void delay()
{
        int counter = 0;
        while(counter < 1000000)
        {
            ++counter;
        }
}
