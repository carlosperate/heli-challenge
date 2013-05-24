/*
 * calibrate.h
 *
 *  Created on: May 10, 2013
 *      Author: Pawel
 */

#ifndef CALIBRATE_H_
#define CALIBRATE_H_
#include "common.h"
#include "joystickservo.h"
#include "joystick.h"

#endif /* CALIBRATE_H_ */

void Calibration(void);
void InitialRead(void);
void ContinuousRead(void);
void StaticRead(void);
uint16 CalibrationStage;
uint16 CalibrationCentreX;
uint16 CalibrationLeft;
uint16 CalibrationUp;
uint16 CalibrationRight;
uint16 CalibrationDown;
uint16 CalibrationCentreY;
uint16 CalibrationDeadRight;
uint16 CalibrationDeadLeft;
uint16 CalibrationDeadUp;
uint16 CalibrationDeadDown;
uint16 CalibrationState;

