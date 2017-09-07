//###########################################################################
// FILE:   blinky.c
// TITLE:  blinky example.
//###########################################################################
// $TI Release: F28M35x Driver Library v100 $
// $Release Date: October 12, 2011 $
//###########################################################################

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED3.
//
//*****************************************************************************

//*****************************************************************************
// The error routine that is called if the driver library encounters an error.
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}

#endif

//*****************************************************************************
// 
// Blink LED3
//*****************************************************************************
int
main(void)
{

    volatile unsigned long ulLoop;

    // Disable Protection
    HWREG(SYSCTL_MWRALLOW) =  0xA5A5A5A5;

    // Sets up PLL, M3 running at 100MHz and C28 running at 100MHz
    SysCtlClockConfigSet(SYSCTL_USE_PLL | (SYSCTL_SPLLIMULT_M & 0xA) |
                         SYSCTL_SYSDIV_1 | SYSCTL_M3SSDIV_1 |
                         SYSCTL_XCLKDIV_4);

    // Enable clock supply for GPIOC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Disable clock supply for the watchdog modules
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG1);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG0);
    
    // Enable processor interrupts.
    IntMasterEnable();

    // Set up the Pin for LED3 
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, ~0);
    
    // Loop forever while the timers run.
    while(1)
    {
        //
        // Turn on the LED.
        //
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
        //
        // Delay for a bit.
        //
        for(ulLoop = 0; ulLoop < 2000000; ulLoop++)
        {
        }
        //
        // Turn off the LED.
        //
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, ~0);
        //
        // Delay for a bit.
        //
        for(ulLoop = 0; ulLoop < 2000000; ulLoop++)
        {
        }

    }
}



