/**
 * @file application.c
 * @date 07/05/2013
 * @author: Carlos Pereira Atencio
 * 
 * Description goes here.
 **************************************************************************** */
#include "application.h"
#include "displaycontrol.h"
#include "timecontrol.h"
#include "joystickservo.h"


/* Module globals */
static ApplicationState_t state = Standby;


/**
 * Function to initialise all the modules and components used in this
 * application.
 * This function is only called once before the scheduler kicks in.
 *************************************************************************** */
inline void initialiseAll(void) {
  time_Init();
  GI2C1_Init();
  display_Init();
  #ifdef DEBUGFLAG
    uart_Init();
    //accelerometer_Init();
  #endif
}


/**
 * Scheduled to run every 50ms without taking in consideration function 
 * runtime. So if runtime takes 10ms, this function will run every 60ms.
 *************************************************************************** */
inline void schedule20HzRelative(void) { 
  /* Very simple machine state */
  /* TODO: Refactor into table driven approach */
  switch(state) {
  case Standby:
    state = stateStandBy();
    break;
  case Play:
    state = statePlay();   
    break;
  case Calibrate:
    state = stateCalibrate();
    break;
  case Difficulty:
    state = stateSelectDifficulty();
    break;
  default:
    #ifdef DEBUGFLAG
      uart_SendStringLn("Default state");
    #endif
    break;
  }
  LED_G_Neg();
}


/**
 * Scheduled to run at a frequency of 50Hz with an absolute time measurement.
 *************************************************************************** */
inline void schedule50HzAbsolute(void) {
  display_FlashAllDigits();
  LED_B_Neg();
}


/**
 * Scheduled to run once a second.
 *************************************************************************** */
inline void schedule1HzAbsolute(void) {
  time_Tick1Sec();
  display_SetByteRight(time_GetSecondsPortion());
  display_SetByteLeft(time_GetMinutesPortion());
  LED_R_Neg();
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t stateStandBy(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Standby.");
    //accelerometer_readXYZ();
    //uart_SendString("Y microseconds: ");
    //uart_SendInt16(js_Move());
    //uart_SendStringLn("\n");  
  #endif 
  
  // Here we check for button states and change state accordingly
    
  return Standby;
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t statePlay(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Play.");
  #endif
  
  return Play;
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t stateCalibrate(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Calibration.");
  #endif 
  
  return Calibrate;
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t stateSelectDifficulty(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Difficulty.");
  #endif
    
  return Difficulty;
}
