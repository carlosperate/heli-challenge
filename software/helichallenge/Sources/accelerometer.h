/**
 * @file accelerometer.h
 * @version 0.1
 * @date 29/04/2013
 * @author: Carlos Pereira Atencio
 * 
 * This library interfaces with the accelerometer in the KL25Z board as a
 * way to test the I2C library. 
 *************************************************************************** */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "common.h"

void accelerometer_Init(void);
void accelerometer_readXYZ(void);

#endif /* ACCELEROMETER_H_ */
