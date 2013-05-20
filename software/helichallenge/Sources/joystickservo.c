/**
 * @file joystickservo.c
 * @date 10/04/2012
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "joystickservo.h"
#include "calibrate.h"

/*Array containing ADC readouts (2 members)*/


/*AdcRead*/
uint16 AdcRead(void){
  uint16 err=AD1_Measure(1);
  AD1_GetValue16(ADC_READOUT);
  return err;
}
//uint16 ConditionADCx(uint16 ADC_X){
//  if ((ADC_X>CalibrationDeadLeft)&&(ADC_X<CalibrationDeadRight)){
//    ADC_X=CalibrationCentreX;
//  }
//  if (ADC>CalibrationDeadRight){
//    ADC=(uint16)(CalibrationCentreX+(CalibrationRight-CalibrationCentreX)*(ADC/65535));
//  }
//  if (ADC<CalibrationDeadLeft){
//    ADC=CalibrationLeft+
//  }
//  return ADC_X;
//}
uint16 ConditionADCx(uint16 ADC_Y){
  if ((ADC_Y>CalibrationDeadLeft)&&(ADC_Y<CalibrationDeadRight)){
    ADC_Y=CalibrationCentreY;
  }

  return ADC_Y;
}
uint16 ConditionADCy(uint16 ADC){
  
return ADC;
}
/** js_AdcToUs
 * Converts the 16bit ADC value from the joystick pots to a value between the
 * minimum and maximum PWM duty cycle.
 * @param adc: The raw ADC data as a 16bit unsigned integer
 * @return A 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */

uint16 js_AdcToUs(uint16 ADC) {
uint16 us=(1000+(uint16)(ADC/65.535));

  return us;
}


/** js_SetServoDutyUsX
 * Description
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void js_SetServoDutyUsX(uint16 us) {
  if (us<1000){
    us=1000;}
  if (us>2000){
    us=2000;}
  us=(word)us;
   PWM1_SetDutyUS(us);
}


/** js_SetServoDutyUsY
 * Description
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void js_SetServoDutyUsY(uint16 us) {
  if (us<1000){
    us=1000;}
  if (us>2000){
    us=2000;}
  us=(word)us;
  PWM2_SetDutyUS(us);
}


/** js_Move
 * Description
 * @param
 * @return
 *************************************************************************** */
uint16 js_Move(void) {
AdcRead();
uint16 us_x=js_AdcToUs(ADC_READOUT[0]);
uint16 us_y=js_AdcToUs(ADC_READOUT[1]);
js_SetServoDutyUsX(us_x);
js_SetServoDutyUsX(us_y);
return us_y;


}


