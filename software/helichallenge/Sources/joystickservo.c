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

/* */
//typedef enum {
//  Button_Trigger, Button_Centre, Button_Left, Button_Right, Button_Box
//} Difficulty_Level_t;


/* Defines for the servo limits */
static const uint16 JOYSTICKSERVO_US_MIN = 1000;
static const uint16 JOYSTICKSERVO_US_MAX =  2000;
static const uint16 JOYSTICKSERVO_US_CENTRE = 1500;


/* */
static const uint8 difficultyTimeSplit = 30;


/** 
 * Converts the 16bit ADC value from the joystick pots to a value between the
 * minimum and maximum PWM duty cycle for the X axis.
 * @param adc: The raw ADC data as a 16bit unsigned integer
 * @return A 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
uint16 js_JoystickToUs(uint16 joystick16BitRange) {
  //uint16 us=(1000+(uint16)(ADC/65.535));
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
  //us=(word)us;
  PWM1_SetDutyUS(us);
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
  //us=(word)us;
  PWM2_SetDutyUS(us);
}


/**
 * Description
 * @return
 *************************************************************************** */
inline uint16 js_GetXUs() {
  return js_JoystickToUs(joystick_GetX());
}


/**
 * Description
 * @return
 *************************************************************************** */
inline uint16 js_GetYUs() {
  return js_JoystickToUs(joystick_GetY());
}


/**
 * Description
 *************************************************************************** */
void js_Move(void) {
  js_SetServoDutyUsY( js_DifficultyAddOffsetY(js_GetYUs()) );
  js_SetServoDutyUsX( js_DifficultyAddOffsetX(js_GetXUs()) );
}



/**
 * Description
 * @param joystickOp
 * @return
 *************************************************************************** */
uint16 js_DifficultyAddOffsetX(uint16 joystickXOp) {
  uint8 difficultyLevel = time_GetTimeInSeconds() / difficultyTimeSplit;
  
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
      joystickXOp += 5000;
      if(joystickXOp<5000) {
        joystickXOp = 65535;
      }
      break;
    case 3:
      // South wind only affects Y
      break;
    default:
      // West wind
      lb_AllLedsOff();
      lb_WestLightOn(TRUE);
      joystickXOp -= 5000;
      if(joystickXOp>60535) {
        joystickXOp = 0;
      }
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
  uint8 difficultyLevel = time_GetTimeInSeconds() / difficultyTimeSplit;
  
  switch(difficultyLevel) {
    case 0:
      // Nothing happens here
      break;
    case 1:
      // North wind
      lb_AllLedsOff();
      lb_NorthLightOn(TRUE);
      joystickYOp -= 5000;
      if(joystickYOp>60535) {
        joystickYOp = 0;
      }
      break;
    case 2:
      // East wind only affects X
      break;
    case 3:
      // South wind
      lb_AllLedsOff();
      lb_SouthLightOn(TRUE);
      joystickYOp += 5000;
      if(joystickYOp<5000) {
        joystickYOp = 65535;
      }
      break;
    default:
      // West wind only affects X
      break;
  }
  return joystickYOp;
}
