/**
 * @file gameplay.h
 * @version 0.3
 * 
 * This library interfaces with the joystick, servo, time and LED blocks 
 * modules to move the platform based on the joystick input and the 
 * current difficulty level.
 * 
 * The difficulty level increases with time, adding "wind" effects.
 * This is achieved by adding an offset to the joystick input before
 * it is fed to the servo module. The LED blocks light up to illustrate the
 * direction of the wind. 
 *************************************************************************** */

#ifndef JOYSTICKSERVO_H_
#define JOYSTICKSERVO_H_

#include "common.h"

/* Function definitions */
void gp_Play(void);
uint8 gp_GetDifficultyLevel(void);
void gp_SetDifficultyLevel(uint8 level);

#endif /* JOYSTICKSERVO_H_ */
