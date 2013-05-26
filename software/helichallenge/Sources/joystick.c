/**
 * @file joystic.h
 * @date 24/05/2013
 * @author: Pawel Kowalski
 *          Carlos Pereira Atencio
 *          
 *************************************************************************** */
#include "joystick.h"
#include "joystickservo.h"


/* A few local globals to define limits and calibration */
static uint16 xMin = 32768;
static uint16 xCentre = 49152;
static uint16 xMax = 65535;
static uint16 yMin = 32768;
static uint16 yCentre = 49152;
static uint16 yMax = 65535;


/**
 * Description
 *************************************************************************** */
bool joystick_isButtonPressed(Joystick_Button_t button) {
  bool value = FALSE;
  
  /* Check one of the four joystick buttons */
  if(button == Button_Trigger) {
    value = Joystick0_GetVal(NULL);
  } else if(button == Button_Centre) {
    value = Joystick1_GetVal(NULL);
  } else if(button == Button_Left) {
    value = Joystick2_GetVal(NULL);
  } else if(button == Button_Right) {
    value = Joystick3_GetVal(NULL);
  } else if(button == Button_Box) {
    value = Boxbutton_GetVal(NULL);
  }
  
  /* Due to a pull up resistor and the button pulling down to ground, reverse */
  if(value == FALSE) {
    value = TRUE;
  } else {
    value = FALSE;
  }
  
  return value;
}


/**
 * Description
 *************************************************************************** */
uint16 AdcRead(void) {
  uint16 err=AD1_Measure(1);
  AD1_GetValue16(ADC_READOUT);
  return err;
}


/**
 * Description
 *************************************************************************** */
uint16 joystick_CalibrateXMin(void) {
  AdcRead();
  xMin = ADC_READOUT[0];
  return xMin;
}

/**
 * Description
 *************************************************************************** */
uint16 joystick_CalibrateXCentre(void) {
  AdcRead();
  xCentre = ADC_READOUT[0];
  return xCentre;
}

/**
 * Description
 *************************************************************************** */
uint16 joystick_CalibrateXMax(void) {
  AdcRead();
  xMax = ADC_READOUT[0];
  return xMax;
}

/**
 * Description
 *************************************************************************** */
uint16 joystick_CalibrateYMin(void) {
  AdcRead();
  yMin = ADC_READOUT[1];
  return yMin;
}

/**
 * Description
 *************************************************************************** */
uint16 joystick_CalibrateYCentre(void) {
  AdcRead();
  yCentre = ADC_READOUT[1];
  return yCentre;
}

/**
 * Description
 *************************************************************************** */
uint16 joystick_CalibrateYMax(void) {
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
  //if ((ADC_Y>CalibrationDeadLeft)&&(ADC_Y<CalibrationDeadRight)){
  //  ADC_Y=CalibrationCentreY;
  //}
  //
  //return ADC_Y;
}


/**
 * Description
 *************************************************************************** */
uint16 ConditionADCy(uint16 ADC){
  
return ADC;
}



/**
 * Description
 *************************************************************************** */
uint16 joystick_GetX() {
  AdcRead();
  float scaleFull16BitRange = 0;
  
  if(ADC_READOUT[0] <= xMin) {
    scaleFull16BitRange = xMin;
  } else if(ADC_READOUT[0] <= xCentre) { 
    scaleFull16BitRange =
      ( (float)(ADC_READOUT[0]-xMin) / (float)(xCentre-xMin) ) * 32767.0f;
  } else if(ADC_READOUT[0] >= xMax) {
    scaleFull16BitRange = xMax;
  } else {
    scaleFull16BitRange =
          ( (float)(ADC_READOUT[0]-(xMin+xCentre)) / (float)(xMax-xCentre) ) * 32768.0f;
  }
    
  return ((uint16) scaleFull16BitRange);
}


/**
 * Description
 *************************************************************************** */
uint16 joystick_GetY() {
  AdcRead();
  float scaleFull16BitRange = 0;
  
  if(ADC_READOUT[0] <= yMin) {
    scaleFull16BitRange = yMin;
  } else if(ADC_READOUT[0] <= yCentre) { 
    scaleFull16BitRange =
      ( (float)(ADC_READOUT[0]-yMin) / (float)(yCentre-yMin) ) * 32767.0f;
  } else if(ADC_READOUT[0] >= yMax) {
    scaleFull16BitRange = yMax;
  } else {
    scaleFull16BitRange =
          ( (float)(ADC_READOUT[0]-(yMin+yCentre)) / (float)(yMax-yCentre) ) * 32768.0f;
  }
  
  return ((uint16) scaleFull16BitRange);
}
