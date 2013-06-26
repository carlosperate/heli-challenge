/**
 * @file servocontrol.c
 *
 **************************************************************************** */
#include "servocontrol.h"


/* Local static globals for the servo limits */
static const uint16 JOYSTICKSERVO_US_MIN = 850;
static const uint16 JOYSTICKSERVO_US_MAX =  1850;
static const uint16 JOYSTICKSERVO_US_CENTRE = 1500;


/* Private functions */
static void servo_DutyUsX(uint16 us);
static void servo_DutyUsY(uint16 us);


/**
 * Enables the the X and Y PWM modules and centres the servo.
 *************************************************************************** */
void servo_Init(void) {
  servo_Start();
  servo_Centre();
  //FRTOS1_vTaskDelay(20/portTICK_RATE_MS);
  //js_ServoStop();
}


/**
 * Enables the the X and Y PWM modules.
 *************************************************************************** */
void servo_Start(void) {
  PWM1_Enable();
  PWM2_Enable();
}


/**
 * Disables the the X and Y PWM modules.
 *************************************************************************** */
void servo_Stop(void) {
  PWM1_Disable();
  PWM2_Disable();
}


/**
 * Positions both X and Y servos to the centre position.
 * It is important to realise that this will configure the PWM output to 
 * request the centre position to the servos. It might take some time for
 * the servos to reach such position.
 *************************************************************************** */
void servo_Centre(void) {
  PWM1_SetDutyUS(JOYSTICKSERVO_US_CENTRE);
  PWM2_SetDutyUS(JOYSTICKSERVO_US_CENTRE);
}


/**
 * Takes a duty cycle in microseconds from the argument and configures the
 * PWM output for the X-axes servo to that duty cycle.
 * @param us 16bit unsigned integer to represent a duty cycle in microseconds
 *           with a range from the minimum and maximum defined in the header
 *           file.
 *************************************************************************** */
void servo_DutyUsX(uint16 us) {
  if(us<JOYSTICKSERVO_US_MIN) {
    us=JOYSTICKSERVO_US_MIN;
  } else if(us>JOYSTICKSERVO_US_MAX) {
    us=JOYSTICKSERVO_US_MAX;
  }

  PWM2_SetDutyUS(us);
}


/**
 * Takes a duty cycle in microseconds from the argument and configures the
 * PWM output for the Y-axes servo to that duty cycle.
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void servo_DutyUsY(uint16 us) {
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
 * Converts the 16bit ADC value from the joystick pots to a value between the
 * minimum and maximum PWM duty cycle for the X axis.
 * @param Full16BitRange: The raw ADC data as a 16bit unsigned integer
 * @return A 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
uint16 servo_16BitsToUs(uint16 Full16BitRange) {
  float usFloat = (float)(JOYSTICKSERVO_US_MAX - JOYSTICKSERVO_US_MIN) *
      (float)Full16BitRange / 65535.0f;
  uint16 us = (uint16)JOYSTICKSERVO_US_MIN + (uint16)usFloat;
  return us;
}


/** 
 * Converts the a 16bit unsigned integer into a scaled value between the
 * minimum and maximum PWM duty cycle for the X axis.
 * @param Full16BitRange 16bit unsigned integer that represents a full scale
 *                       of values
 *************************************************************************** */
void servo_Duty16BitX(uint16 Full16BitRange) {
  servo_DutyUsX(servo_16BitsToUs(Full16BitRange));
}


/** 
 * Converts the a 16bit unsigned integer into a scaled value between the
 * minimum and maximum PWM duty cycle for the X axis.
 * @param Full16BitRange 16bit unsigned integer that represents a full scale
 *                       of values
 *************************************************************************** */
void servo_Duty16BitY(uint16 Full16BitRange) {
  servo_DutyUsY(servo_16BitsToUs(Full16BitRange));
}
