/**
 * @file accelerometer.c
 * @date 29/04/2013
 * @author: Carlos Pereira Atencio
 * 
 * This code will have very few comments as it is only used for temporary 
 * testing of the I2C.
 **************************************************************************** */
#include "accelerometer.h"
#include "GI2C1.h"
#ifdef DEBUGFLAG
  #include "uartcontrol.h"
#endif


/** I2C address of MMA8451 accelerometer */
#define MMA8451_I2C_ADDRESS 0x1D

/** External 3-axis accelerometer control register addresses */
#define MMA8451_CTRL_REG_1 0x2A

/** MMA8451 3-axis accelerometer control register bit masks */
#define MMA8451_ACTIVE_BIT_MASK 0x01
#define MMA8451_F_READ_BIT_MASK 0x02
 
/** External 3-axis accelerometer data register addresses */
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06


/**
 * Initialises the accelerometer settings using the I2C protocol.
 *************************************************************************** */
void accelerometer_Init(void) { 
  /* Configure the accelerometer */
  uint8 registerWrite = MMA8451_CTRL_REG_1;
  uint8 configuration = MMA8451_F_READ_BIT_MASK|MMA8451_ACTIVE_BIT_MASK;
  GI2C1_WriteAddress(MMA8451_I2C_ADDRESS, &registerWrite, 1, &configuration,
      1);
}


/**
 * Gets the X, Y and Z values of the accelerometer in the KL25Z board and
 * sends the data to the UART peripheral if debug mode is active.
 *************************************************************************** */
void accelerometer_readXYZ(void) { 
  uint8 registerRead = MMA8451_OUT_X_MSB;
  int8 xyz[3] = {0, 1, 2};
  GI2C1_ReadAddress(MMA8451_I2C_ADDRESS, &registerRead, 1, (uint8_t*)&xyz, 3);
  #ifdef DEBUGFLAG
    uart_SendString("X: ");
    uart_SendByte(xyz[0]);
    uart_SendString("; Y: ");
    uart_SendByte(xyz[1]);
    uart_SendString("; Z: ");
    uart_SendByte(xyz[2]);
    uart_SendStringLn(";");
  #endif
}
