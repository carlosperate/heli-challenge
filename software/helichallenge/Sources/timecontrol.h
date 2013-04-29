/**
 * @file timecontrol.h
 * @version 0.1
 * @date 28/04/2013
 * @author Carlos Pereira Atencio
 * 
 * This module is responsible to maintain the track of the time elapsed since
 * the beggining of the game.
 * 
 * The function Tick1Sec has to be called by the RTOS every second.
 *************************************************************************** */

#ifndef TIMECONTROL_H_
#define TIMECONTROL_H_

#include "common.h"

void time_Init();
void time_Tick1Sec();
void time_Start();
void time_Pause();
void time_End();
void time_Reset();
uint16 time_GetTimeInSeconds();
uint8 time_GetTimeInMinutes();
uint8 time_GetSecondsPortion();
uint8 time_GetMinutesPortion();
void time_SetTimeFromSeconds(uint16 seconds);

#endif /* TIMECONTROL_H_ */
