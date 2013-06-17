/**
 * @file joystickservo.c
 * @date 23/05/2013
 * @author: Carlos Pereira Atencio
 *          Pawel
 **************************************************************************** */
#include "joystickservo.h"
#include "joystick.h"
#include "timecontrol.h"
#include "ledblocks.h"


/* Defines for the servo limits */
static const uint16 JOYSTICKSERVO_US_MIN = 850;
static const uint16 JOYSTICKSERVO_US_MAX =  1850;
static const uint16 JOYSTICKSERVO_US_CENTRE = 1500;


/* Local globals */
static const uint8 difficultyTimeSplit = 30;
static uint8 difficultyLevel;


void js_CalculateDifficultyLevel(void);

/** 
 * Converts the 16bit ADC value from the joystick pots to a value between the
 * minimum and maximum PWM duty cycle for the X axis.
 * @param adc: The raw ADC data as a 16bit unsigned integer
 * @return A 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
uint16 js_JoystickToUs(uint16 joystick16BitRange) {
  float usFloat = (float)(JOYSTICKSERVO_US_MAX - JOYSTICKSERVO_US_MIN) *
      (float)joystick16BitRange / 65535.0f;
  uint16 us = (uint16)JOYSTICKSERVO_US_MIN + (uint16)usFloat;
  return us;
}


/** js_SetServoDutyUsX
 * Description
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void js_SetServoDutyUsX(uint16 us) {
  if(us<JOYSTICKSERVO_US_MIN) {
    us=JOYSTICKSERVO_US_MIN;
  } else if(us>JOYSTICKSERVO_US_MAX) {
    us=JOYSTICKSERVO_US_MAX;
  }

  PWM2_SetDutyUS(us);
}


/**
 * Description
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void js_SetServoDutyUsY(uint16 us) {
  if(us<JOYSTICKSERVO_US_MIN) {
    us=JOYSTICKSERVO_US_MIN;
  } else if(us>JOYSTICKSERVO_US_MAX) {
    us=JOYSTICKSERVO_US_MAX;
  }

  /* Inverting the Y axis*/
  us = JOYSTICKSERVO_US_MAX - us  + JOYSTICKSERVO_US_MIN;
  PWM1_SetDutyUS(us);
}


/**
 * Description
 * @return
 *************************************************************************** */
inline uint16 js_GetXUs(void) {
  return js_JoystickToUs(joystick_GetX());
}


/**
 * Description
 * @return
 *************************************************************************** */
inline uint16 js_GetYUs(void) {
  return js_JoystickToUs(joystick_GetY());
}


/**
 * Description
 *************************************************************************** */
void js_Move(void) {
  js_CalculateDifficultyLevel();
  js_SetServoDutyUsY( js_DifficultyAddOffsetY(js_GetYUs()) );
  js_SetServoDutyUsX( js_DifficultyAddOffsetX(js_GetXUs()) );
}


/**
 * Description
 *************************************************************************** */
void js_ServoStart(void) {
  PWM1_Enable();
  PWM2_Enable();
}


/**
 * Description
 *************************************************************************** */
void js_ServoStop(void) {
  PWM1_Disable();
  PWM2_Disable();
}


/**
 * Description
 *************************************************************************** */
void js_ServoCentre(void) {
  PWM1_SetDutyUS(JOYSTICKSERVO_US_CENTRE);
  PWM2_SetDutyUS(JOYSTICKSERVO_US_CENTRE);
}


/**
 * Description
 *************************************************************************** */
void js_ServoInit(void) {
  js_ServoStart();
  js_ServoCentre();
  //FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  //js_ServoStop();
}


/**
 * Description
 * @param joystickOp
 * @return
 *************************************************************************** */
uint16 js_DifficultyAddOffsetX(uint16 joystickXOp) {
  
  switch(difficultyLevel) {
    case 0:
      // Nothing happens here
      break;
    case 1:
      // North wind only affects Y
      break;
    case 2:
      // East wind
      lb_AllLedsOff();
      lb_EastLightOn(TRUE);
      joystickXOp += 275;
      break;
    case 3:
      // South wind only affects Y
      break;
    case 4:
      // West wind
      lb_AllLedsOff();
      lb_WestLightOn(TRUE);
      joystickXOp -= 225;
      break;
    case 5:
       // North & East
      lb_EastLightOn(TRUE);
      lb_WestLightOn(FALSE);
      joystickXOp += 275;
      break;
    case 6: 
      // South & West
      lb_EastLightOn(FALSE);
      lb_WestLightOn(TRUE);
      joystickXOp -= 225;
      break;
    default:
      lb_AllLedsOff();
      break;
  }
  return joystickXOp;
}

/**
 * Description
 * @param joystickOp
 * @return
 *************************************************************************** */
uint16 js_DifficultyAddOffsetY(uint16 joystickYOp) {

  switch(difficultyLevel) {
    case 0:
      // Nothing happens here
      break;
    case 1:
      // North wind
      lb_AllLedsOff();
      lb_NorthLightOn(TRUE);
      joystickYOp -= 275;
      break;
    case 2:
      // East wind only affects X
      break;
    case 3:
      // South wind
      lb_AllLedsOff();
      lb_SouthLightOn(TRUE);
      joystickYOp += 225;
      break;
    case 4:
      // Wesr wind only affects X
      break;
    case 5:
       // North & East
      lb_SouthLightOn(FALSE);
      lb_NorthLightOn(TRUE);
      joystickYOp -= 275;
      break;
    case 6: 
      // South & West
      lb_SouthLightOn(TRUE);
      lb_NorthLightOn(FALSE);
      joystickYOp += 225;
      break;
    default:
      //lb_AllLedsOff();
      // West wind only affects X
      break;
  }
  return joystickYOp;
}


/**
 * Description
 * @return
 *************************************************************************** */
void js_CalculateDifficultyLevel(void) {
  difficultyLevel = (uint8)(time_GetTimeInSeconds() / difficultyTimeSplit);
}


/**
 * Description
 * @return
 *************************************************************************** */
uint8 js_GetDifficultyLevel(void) {
  return difficultyLevel;
}
