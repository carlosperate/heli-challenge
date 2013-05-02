/**
 * @file application.c
 * @date 29/04/2013
 * @author: Carlos Pereira Atencio
 * 
 * Description goes here.
 **************************************************************************** */
#include "application.h"
#include "displaycontrol.h"
#include "timecontrol.h"
#ifdef DEBUGFLAG
  #include "uartcontrol.h"
  #include "accelerometer.h"
#endif


/**
 * Function to initialise all the modules and components used in this
 * application.
 *************************************************************************** */
void initialiseAll(void) {
  time_Init();
  GI2C1_Init();
  display_Init();
  #ifdef DEBUGFLAG
    uart_Init();
    accelerometer_Init();
  #endif
}


/**
 * Description goes here.
 *************************************************************************** */
void schedule50HzAbsolute(void) {
  display_FlashAllDigits();
}

/**
 * Description goes here.
 *************************************************************************** */
void schedule1HzAbsolute(void) {
  time_Tick1Sec();
}
