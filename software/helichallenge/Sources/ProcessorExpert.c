/** ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-03-08, 14:31, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "FRTOS1.h"
#include "RTOSTICKLDD1.h"
#include "UTIL1.h"
#include "LED_R.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LED_B.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LED_G.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"
#include "AS1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PWM2.h"
#include "PwmLdd2.h"
#include "TU2.h"
#include "GI2C1.h"
#include "I2C2.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "Joystick0.h"
#include "Joystick3.h"
#include "Joystick4.h"
#include "Joystick2.h"
#include "LED_North.h"
#include "LED_South.h"
#include "LED_East.h"
#include "LED_West.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "application.h"
#include "scheduler.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  initialiseAll();
  createTasks();  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
