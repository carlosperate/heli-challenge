/**
 * @file application.c
 * @date 23/05/2013
 * @author: Carlos Pereira Atencio
 * 
 * Description goes here.
 **************************************************************************** */
#include "application.h"
#include "displaycontrol.h"
#include "timecontrol.h"
#include "joystickservo.h"
#include "calibrate.h"
#include "Button_LED_Test.h"
#include "Debug.h"
#include "TSS1.h"

/* Module globals */
static ApplicationState_t state = Standby;


/**
 * Function to initialise all the modules and components used in this
 * application.
 * This function is only called once before the scheduler kicks in.
 *************************************************************************** */
inline void initialiseAll(void) {
  //PWM1_Disable();
  //PWM2_Disable();
  time_Init();
  GI2C1_Init();
  display_Init();
  //InitialRead();
  TSS1_Configure();
  #ifdef DEBUGFLAG
    uart_Init();
    //accelerometer_Init();
  #endif
  PWM1_Enable();
  PWM2_Enable();
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
  
  TSS_Task();
}


/**
 * Scheduled to run at a frequency of 50Hz with an absolute time measurement.
 *************************************************************************** */
inline void schedule250HzAbsolute(void) {
  display_FlashAllDigits();
  LED_G_Neg();
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
    //uart_SendStringLn("Standby.");
    DebugJoystickADC();
    DebugJoystickButtons();
  #endif 
  
  // Here we check for button states and change state accordingly

  js_Move();
  return Standby;
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t statePlay(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Play.");
    DebugJoystickADC();
    DebugJoystickButtons();
  #endif
  js_Move();
  return Play;
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t stateCalibrate(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Calibration.");
  #endif 
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  uint16 ADCtemp = 0;
  
  /** Start by setting X centre position. */
  while(!Get_Value(0)) {
    ADCtemp = js_CalibrateXCentre();
  }
  #ifdef DEBUGFLAG
    uart_SendString("X Centre: ");
    uart_SendUInt16(ADCtemp);
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Then minimum X position (right). */
  while(!Get_Value(0)) {
    ADCtemp = js_CalibrateXMin();
  }
  #ifdef DEBUGFLAG
    uart_SendString("\r\nX Min: ");
    uart_SendUInt16(ADCtemp);
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Then maximum X (left). */
  while(!Get_Value(0)) {
    ADCtemp = js_CalibrateXMax();
  }
  #ifdef DEBUGFLAG
    uart_SendString("\r\nX Max: ");
    uart_SendUInt16(ADCtemp);
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Followed by Y centre. */
  while(!Get_Value(0)) {
    ADCtemp = js_CalibrateYCentre();
  }
  #ifdef DEBUGFLAG
    uart_SendString("\r\nY Centre: ");
    uart_SendUInt16(ADCtemp);
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Then minimum Y (down). */
  while(!Get_Value(0)) {
    ADCtemp = js_CalibrateYMin();
  }
  #ifdef DEBUGFLAG
    uart_SendString("\r\nY Min: ");
    uart_SendUInt16(ADCtemp);
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** And finally maximum Y (up). */
  while(!Get_Value(0)) {
    ADCtemp = js_CalibrateYMax();
  }
  #ifdef DEBUGFLAG
    uart_SendString("\r\nY Max: ");
    uart_SendUInt16(ADCtemp);
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
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



/**
 * Test mode to check the hardware and software is working correctly.
 *************************************************************************** */
ApplicationState_t stateTestMode(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Test Mode.");
  #endif
    
  // Test the LEDs
  TestLEDs();
  // Test the servos
  // Test the joystick
    
  return Test;
}
