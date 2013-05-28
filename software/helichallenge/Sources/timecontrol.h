/**
 * @file timecontrol.h
 * @version 0.1
 * @date 28/04/2013
 * @author Carlos Pereira Atencio
 * 
 * This module is responsible to maintain track of the time elapsed since
 * the beginning of the game.
 * 
 * The function Tick1Sec has to be called by the RTOS every second.
 *************************************************************************** */

#ifndef TIMECONTROL_H_
#define TIMECONTROL_H_

#include "common.h"

void time_Init(void);
void time_Tick1Sec(void);
void time_Start(void);
void time_Restart(void);
void time_Pause(void);
void time_End(void);
void time_Reset(void);
uint16 time_GetTimeInSeconds(void);
uint8 time_GetTimeInMinutes(void);
uint8 time_GetSecondsPortion(void);
uint8 time_GetMinutesPortion(void);
void time_SetTimeFromSeconds(uint16 seconds);

#endif /* TIMECONTROL_H_ */
