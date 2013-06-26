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
#include "joystick.h"
#include "servocontrol.h"
#include "gameplay.h"
#include "TSS1.h"
#include "debug.h"
#include "ledblocks.h"
//#include "FreeMASTER/freemaster.h"


/* Module globals */
static ApplicationState_t state = Standby;


/* Local functions */
void debugJoystickServo(void);


/**
 * Function to initialise all the modules and components used in this
 * application.
 * This function is only called once before the scheduler kicks in.
 *************************************************************************** */
inline void initialiseAll(void) {
  time_Init();
  display_Init();
  TSS1_Configure();
  //FMSTR_Init();
  servo_Start();
  //js_ServoStop();
  #ifdef DEBUGFLAG
    uart_Init();
    //accelerometer_Init();
    uart_SendStringLn("Booted");
  #endif
}


/**
 * Scheduled to run at a frequency of 50Hz with an absolute time measurement.
 *************************************************************************** */
inline void schedule500HzAbsolute(void) {
  display_FlashAllDigits();
  LED_G_Neg();
}


/**
 * Scheduled to run every 50ms without taking in consideration function 
 * runtime. So if runtime takes 10ms, this function will run every 60ms.
 *************************************************************************** */
inline void schedule40HzRelative(void) { 
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
    case Test:
      state = stateTestMode();
      break;
    default:
      #ifdef DEBUGFLAG
        uart_SendStringLn("Default state.");
      #endif
      break;
  }
  //FMSTR_Recorder();
  //FMSTR_Poll();
  TSS_Task();
}


/**
 * Scheduled to run once a second.
 *************************************************************************** */
inline void schedule1HzAbsolute(void) {
  #ifdef DEBUGFLAG
    //uart_SendStringLn("Tick");
  #endif 
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
    //debug_JoystickServo();
  #endif 
  
  /* We first check for box button for special modes */
  if(joystick_isButtonPressed(Button_Box) == TRUE) {
    if(joystick_isButtonPressed(Button_Centre) == TRUE) {
      return Calibrate;
    } else if(joystick_isButtonPressed(Button_Left) == TRUE) {
      return Test;
    } else if(joystick_isButtonPressed(Button_Trigger) == TRUE) {
      return Difficulty; 
    } else {
      return Standby; 
    }
  } else if(joystick_isButtonPressed(Button_Trigger) == TRUE) {
    return Play; 
  }

  return Standby;
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t statePlay(void) {
  /* Restart the PWM peripherals (servos) and time module */
  servo_Start();
  time_Restart();
  
  /* Game last for as long as the trigger or box button is pressed 
   * or until the capacitive sensor detects the ball touching the edge */
  while( (joystick_isButtonPressed(Button_Trigger) == TRUE)
      && (joystick_isButtonPressed(Button_Box) == FALSE)
      /*&& (js_GetDifficultyLevel <=6)*/) {
    gp_Play();
    #ifdef DEBUGFLAG
      debug_PlayData();
    #endif
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
  
  /* Out of the loop means game over, so deactivate PWM and time module*/
  time_End();
  FRTOS1_vTaskDelay(3500/portTICK_RATE_MS);
  servo_Centre();
  lb_AllLedsOff();
  FRTOS1_vTaskDelay(310/portTICK_RATE_MS);
  servo_Stop();
  
  return Standby;
}


/**
 * Description
 *************************************************************************** */
ApplicationState_t stateCalibrate(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Calibration.");
    uart_SendString("X Centre: ");
  #endif 
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  uint16 ADCtemp = 0;
  lb_AllLedsOn(); /* All four means centre */
  
  /** Start by setting X centre position. */
  while(!joystick_isButtonPressed(Button_Centre)) {
    ADCtemp = joystick_CalibrateXCentre();
    display_SetUint16(ADCtemp/10);
  }
  lb_AllLedsOff();
  lb_EastLightOn(TRUE);
  #ifdef DEBUGFLAG
    uart_SendUInt16(ADCtemp);
    uart_SendString("\r\nX Min: ");
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Then minimum X position (right). */
  while(!joystick_isButtonPressed(Button_Centre)) {
    ADCtemp = joystick_CalibrateXMin();
    display_SetUint16(ADCtemp/10);
  }
 
  lb_EastLightOn(FALSE);
  lb_WestLightOn(TRUE);
  #ifdef DEBUGFLAG
    uart_SendUInt16(ADCtemp);
    uart_SendString("\r\nX Max: ");
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Then maximum X (left). */
  while(!joystick_isButtonPressed(Button_Centre)) {
    ADCtemp = joystick_CalibrateXMax();    
    display_SetUint16(ADCtemp/10);
  }
  lb_AllLedsOn();
  #ifdef DEBUGFLAG
    uart_SendUInt16(ADCtemp);
    uart_SendString("\r\nY Centre: ");
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Followed by Y centre. */
  while(!joystick_isButtonPressed(Button_Centre)) {
    ADCtemp = joystick_CalibrateYCentre();
    display_SetUint16(ADCtemp/10);
  }
  lb_AllLedsOff();
  lb_SouthLightOn(TRUE);
  #ifdef DEBUGFLAG
    uart_SendUInt16(ADCtemp);
    uart_SendString("\r\nY Min: ");
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** Then minimum Y (down). */
  while(!joystick_isButtonPressed(Button_Centre)) {
    ADCtemp = joystick_CalibrateYMin();
    display_SetUint16(ADCtemp/10);
  }
  lb_SouthLightOn(FALSE);
  lb_NorthLightOn(TRUE);
  #ifdef DEBUGFLAG
    uart_SendUInt16(ADCtemp);
    uart_SendString("\r\nY Max: ");
  #endif
  FRTOS1_vTaskDelay(750/portTICK_RATE_MS);
  
  /** And finally maximum Y (up). */
  while(!joystick_isButtonPressed(Button_Centre)) {
    ADCtemp = joystick_CalibrateYMax();
    display_SetUint16(ADCtemp/10);
  }
  lb_AllLedsOff();
  #ifdef DEBUGFLAG
    uart_SendUInt16(ADCtemp);
  #endif
  FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
  
  return Standby;
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
  //lb_TestAllLightsIntervaMs(1000);
  // Test the servos
  // Test the joystick
  
  debug_Leds();
  
  return Test;
}

