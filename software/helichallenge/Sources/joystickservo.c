/**
 * @file joystickservo.c
 * @date 23/05/2013
 * @author: Carlos Pereira Atencio
 *          Pawel
 **************************************************************************** */
#include "joystickservo.h"
#include "calibrate.h"


/* Defines for the servo limits */
static const uint16 JOYSTICKSERVO_US_MIN = 1000;
static const uint16 JOYSTICKSERVO_US_MAX =  2000;
static const uint16 JOYSTICKSERVO_US_CENTRE = 1500;


/* A few local globals to define limitis and calibration */
static uint16 xMin = 32768;
static uint16 xCentre = 49152;
static uint16 xMax = 65535;
static uint16 yMin = 32768;
static uint16 yCentre = 49152;
static uint16 yMax = 65535;


/**
 * Description
 *************************************************************************** */
uint16 AdcRead(void){
  uint16 err=AD1_Measure(1);
  AD1_GetValue16(ADC_READOUT);
  return err;
}


/**
 * Description
 *************************************************************************** */
uint16 js_CalibrateXMin(void) {
  AdcRead();
  xMin = ADC_READOUT[0];
  return xMin;
}

/**
 * Description
 *************************************************************************** */
uint16 js_CalibrateXCentre(void) {
  AdcRead();
  xCentre = ADC_READOUT[0];
  return xCentre;
}

/**
 * Description
 *************************************************************************** */
uint16 js_CalibrateXMax(void) {
  AdcRead();
  xMax = ADC_READOUT[0];
  return xMax;
}

/**
 * Description
 *************************************************************************** */
uint16 js_CalibrateYMin(void) {
  AdcRead();
  yMin = ADC_READOUT[1];
  return yMin;
}

/**
 * Description
 *************************************************************************** */
uint16 js_CalibrateYCentre(void) {
  AdcRead();
  yCentre = ADC_READOUT[1];
  return yCentre;
}

/**
 * Description
 *************************************************************************** */
uint16 js_CalibrateYMax(void) {
  AdcRead();
  yMax = ADC_READOUT[1];
  return yMax;
}


/**
 * Description
 *************************************************************************** */
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


/**
 * Description
 *************************************************************************** */
uint16 ConditionADCy(uint16 ADC){
  
return ADC;
}


/** 
 * Converts the 16bit ADC value from the joystick pots to a value between the
 * minimum and maximum PWM duty cycle for the Y axis.
 * @param adc: The raw ADC data as a 16bit unsigned integer
 * @return A 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
uint16 js_AdcToUsX(uint16 ADC) {
  //uint16 us=(1000+(uint16)(ADC/65.535));
  float percentageAdcRange = (float)(ADC-xMin) / (float)(xMax-xMin);
  float usFloat = (float)(JOYSTICKSERVO_US_MAX - JOYSTICKSERVO_US_MIN) *
      percentageAdcRange;
  uint16 us = (uint16)JOYSTICKSERVO_US_MIN + (uint16)usFloat;
  return us;
}


/** 
 * Converts the 16bit ADC value from the joystick pots to a value between the
 * minimum and maximum PWM duty cycle for the X axis.
 * @param adc: The raw ADC data as a 16bit unsigned integer
 * @return A 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
uint16 js_AdcToUsY(uint16 ADC) {
  //uint16 us=(1000+(uint16)(ADC/65.535));
  float percentageAdcRange = (float)(ADC-yMin) / (float)(yMax-yMin);
  float usFloat = (float)(JOYSTICKSERVO_US_MAX - JOYSTICKSERVO_US_MIN) *
      percentageAdcRange;
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
  }
  else if(us>JOYSTICKSERVO_US_MAX) {
    us=JOYSTICKSERVO_US_MAX;
  }
  //us=(word)us;
  PWM1_SetDutyUS(us);
}


/** js_SetServoDutyUsY
 * Description
 * @param us: 16bit unsigned integer to represent a duty cycle in microseconds
 * with a range from the minimum and maximum defined in the header file.
 *************************************************************************** */
void js_SetServoDutyUsY(uint16 us) {
  if(us<JOYSTICKSERVO_US_MIN) {
    us=JOYSTICKSERVO_US_MIN;
  }
  else if(us>JOYSTICKSERVO_US_MAX) {
    us=JOYSTICKSERVO_US_MAX;
  }
  //us=(word)us;
  PWM2_SetDutyUS(us);
}


/** js_Move
 * Description
 * @param
 * @return
 *************************************************************************** */
void js_Move(void) {
  AdcRead();
  uint16 us_x=js_AdcToUsX(ADC_READOUT[0]);
  uint16 us_y=js_AdcToUsY(ADC_READOUT[1]);
  js_SetServoDutyUsX(us_x);
  js_SetServoDutyUsY(us_y);
}


