/**
 * @file accelerometer.c
 * @date 11/04/2012
 * @author: Carlos Pereira Atencio
 * 
 * This code will have very few comments as it is only used for temporary 
 * texting
 **************************************************************************** */
#include "joystickservo.h"
#include "GI2C1.h"
#include "uartcontrol.h"

/* I2C address of MMA8451 accelerometer */
#define MMA8451_I2C_ADDRESS 0x1D
/* External 3-axis accelerometer control register addresses */
#define MMA8451_CTRL_REG_1 0x2A
/* MMA8451 3-axis accelerometer control register bit masks */
#define MMA8451_ACTIVE_BIT_MASK 0x01
#define MMA8451_F_READ_BIT_MASK 0x02
 
/* External 3-axis accelerometer data register addresses */
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06

/** readXYZ
 * Get the X, Y and Z values of the accelerometer in the KL25Z board.
 * @return A 16bit signed integer to represent the X value.
 *************************************************************************** */
int16 accelerometer_readXYZ(void) {
  #ifdef DEBUGFLAG
    uart_SendStringLn("Test");
  #endif
  /* Configure the accelerometer */
  byte one = MMA8451_CTRL_REG_1;
  byte two = MMA8451_F_READ_BIT_MASK|MMA8451_ACTIVE_BIT_MASK;
  byte three = MMA8451_OUT_X_MSB;
  byte res = GI2C1_WriteAddress(MMA8451_I2C_ADDRESS, &one, 1,
      &two, 1);
  if (res==ERR_OK) {
    int8 xyz[3];
    xyz[0]=0;xyz[1]=1;xyz[2]=2;
    res = GI2C1_ReadAddress(MMA8451_I2C_ADDRESS,
        &three, 1, (uint8_t*)&xyz, 3);
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
  return 0;
}

