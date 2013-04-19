/**
 * @file accelerometer.h
 * @version 0.1
 * @date 11/04/2012
 * @author: Carlos Pereira Atencio
 * 
 * This library interfaces with the accelerometer in the KL25Z board as a
 * way to test the I2C library. 
 *************************************************************************** */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "common.h"

int16 accelerometer_readXYZ(void);

#endif /* ACCELEROMETER_H_ */
