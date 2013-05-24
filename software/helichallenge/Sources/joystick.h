/**
 * @file joystickservo.h
 * @version 0.2
 * @date 24/05/2013
 * @author: Pawel Kowalski
 *          Carlos Pereira Atencio
 *          
 * Description should go here asap.
 *************************************************************************** */
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "common.h"

/* Typedef to easily identify the buttons in the joystick */
typedef enum {
  Button_Trigger, Button_Centre, Button_Left, Button_Right
} Joystick_Button_t;

/* Global array containing ADC readouts (2 members)*/
uint16 ADC_READOUT[AD1_CHANNEL_COUNT];

/* Function definitions */
bool joystick_isButtonPressed(uint8 SignalName);
void joystick_DebugADCXYServo();
void joystick_DebugButtons();
uint16 joystick_CalibrateXMin(void);
uint16 joystick_CalibrateXCentre(void);
uint16 joystick_CalibrateXMax(void);
uint16 joystick_CalibrateYMin(void);
uint16 joystick_CalibrateYCentre(void);
uint16 joystick_CalibrateYMax(void);
uint16 ConditionADCx(uint16 ADC_X);
uint16 ConditionADCy(uint16 ADC_Y);
uint16 joystick_GetX();
uint16 joystick_GetY();

#endif /* JOYSTICK_H_ */
