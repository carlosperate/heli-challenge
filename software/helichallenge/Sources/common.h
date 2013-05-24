/**
 * @file common.h
 * @version 0.1
 * @date 02/05/2013
 * @author: Carlos Pereira Atencio
 * 
 * To contain all common library includes and global variables.
 *************************************************************************** */

#ifndef COMMON_H_
#define COMMON_H_

/* The following filetypes have been defined in the respective file.
 * PE_Types.h: bool, int8, uint8, byte, int16, ,uint16, int32, uint32; */
#include "PE_Types.h"

/* The following is used to add UART(USB) messages for debugging */
#ifndef DEBUGFLAG
  #define DEBUGFLAG
  #include "uartcontrol.h"
  #include "accelerometer.h"
#endif

#endif /* COMMON_H_ */
