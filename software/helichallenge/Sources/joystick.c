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
    value = TRUE;//Joystick2_GetVal(NULL);
  } else if(button == Button_Right) {
    value = TRUE;//Joystick3_GetVal(NULL);
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
uint16 joystick_GetX() {
  AdcRead();
  float scaleFull16BitRange = 0;
  uint16 returnvalue = 0;
  
  if(ADC_READOUT[0] <= xMin) {
    returnvalue = 0;
  } else if(ADC_READOUT[0] >= xMax) {
    returnvalue = 65535;
  } else if(ADC_READOUT[0] <= xCentre) { 
    scaleFull16BitRange =
      ( (float)(ADC_READOUT[0]-xMin) / (float)(xCentre-xMin) ) * 32767.0f;
    returnvalue = (uint16)scaleFull16BitRange;
  } else {
    scaleFull16BitRange =
          ( (float)(ADC_READOUT[0]-xCentre) / (float)(xMax-xCentre) ) * 32768.0f;
    returnvalue = 32767 + (uint16)scaleFull16BitRange;
  }
  
  return returnvalue;
}


/**
 * Description
 *************************************************************************** */
uint16 joystick_GetY() {
  AdcRead();
  float scaleFull16BitRange = 0;
  uint16 returnvalue = 0;
  
  if(ADC_READOUT[1] <= yMin) {
    returnvalue = 0;
  } else if(ADC_READOUT[1] >= yMax) {
    returnvalue = 65535;
  } else if(ADC_READOUT[1] <= yCentre) { 
    scaleFull16BitRange =
      ( (float)(ADC_READOUT[1]-yMin) / (float)(yCentre-yMin) ) * 32767.0f;
    returnvalue = (uint16)scaleFull16BitRange;
  } else {
    scaleFull16BitRange =
          ( (float)(ADC_READOUT[1]-yCentre) / (float)(yMax-yCentre) ) * 32768.0f;
    returnvalue = 32767 + (uint16)scaleFull16BitRange;
  }
  
  return returnvalue;
}
