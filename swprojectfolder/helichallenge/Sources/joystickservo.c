/**
 * @file joystickservo.c
 * @date 10/04/2012
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "joystickservo.h"


/** js_AdcToUs
 * Converts the 16bit ADC value from the joystick pots to a value between the
 * minimum and maximum PWM duty cycle.
 * @param adc: The raw ADC data as a 16bit unsigned integer
 * @return A 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
uint16 js_AdcToUs(uint16 adc) {
  
  return 0;
}


/** js_SetServoDutyUsX
 * Description
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void js_SetServoDutyUsX(uint16 us) {
  // Remember to sanitise the input
  // function call is PWM1_SetDutyUS
}


/** js_SetServoDutyUsY
 * Description
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void js_SetServoDutyUsY(uint16 us) {
  // Remember to sanitise the input
  // function call is PWM2_SetDutyUS
}


/** js_Move
 * Description
 * @param
 * @return
 *************************************************************************** */
void js_Move(void) {
  // Pull ADC value for X joystick
  // Convert ADC to microseconds
  // Set servo X to the value above
  // Do the same for Y
}
