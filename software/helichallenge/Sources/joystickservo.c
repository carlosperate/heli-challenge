/**
 * @file joystickservo.c
 * @date 23/05/2013
 * @author: Carlos Pereira Atencio
 *          Pawel
 **************************************************************************** */
#include "joystickservo.h"
#include "joystick.h"


/* Defines for the servo limits */
static const uint16 JOYSTICKSERVO_US_MIN = 1000;
static const uint16 JOYSTICKSERVO_US_MAX =  2000;
static const uint16 JOYSTICKSERVO_US_CENTRE = 1500;


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
  js_SetServoDutyUsY(js_GetYUs());
  js_SetServoDutyUsX(js_GetXUs());
}
