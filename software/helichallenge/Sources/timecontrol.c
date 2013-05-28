/**
 * @file timecontrol.c
 * @date 28/04/2013
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "timecontrol.h"

/* Constants */
const static uint8 maxMinutes = 10;


/* Local globals */
static uint16 timeInSeconds = 0;
static uint8 timeSecondsPart = 0;
static uint8 timeMinutesPart = 0;
static bool isRunning = FALSE;


/** 
 * Initialises all the settings of the elapsed game time.
 *************************************************************************** */
void time_Init(void) {
  time_Reset();
}


/** 
 * Function to be called once every seconds by the RTOS.
 * When the game has stated, it adds one second to the counter and stores the
 * time in total seconds and a "minutes and seconds" format.
 *************************************************************************** */
void time_Tick1Sec(void) {
  if(isRunning) {
    timeSecondsPart++;
    
    /* Convert current seconds to minutes+seconds */
    if(timeSecondsPart>59) {
      timeMinutesPart++;
      timeSecondsPart = 0;
      
      /* Check if maximum defined time has been reached */
      if(timeMinutesPart>(maxMinutes-1)) {
        time_End();
      }
    }
  }
}


/** 
 * Indicates the start of the counting
 * time_Tick1Sec function to count time.
 *************************************************************************** */
void time_Start(void) {
  isRunning = TRUE;
}


/** 
 * Resets all settings and indicates the start of the game and allows the
 * time_Tick1Sec function to count time.
 *************************************************************************** */
void time_Restart(void) {
  time_Reset();
  isRunning = TRUE;
}



/** 
 * Pauses the current game time counter.
 *************************************************************************** */
void time_Pause(void) {
  isRunning = FALSE;
}


/** 
 * Ends the game counter.
 *************************************************************************** */
void time_End(void) {
  isRunning = FALSE;
}


/** 
 * Resets all the timer settings.
 *************************************************************************** */
void time_Reset(void) {
  timeInSeconds = 0;
  timeSecondsPart = 0;
  timeMinutesPart = 0;
  isRunning = FALSE;
}


/** 
 * Returns the time in total seconds.
 * @return The seconds in an unsigned 16 bits integer
 *************************************************************************** */
uint16 time_GetTimeInSeconds(void) {
  return timeInSeconds;
}


/** 
 * Returns the time in total minutes, rounding to the closes minute.
 * @return The minutes as defined in the description in an unsigned 8 bits
 *         integer
 *************************************************************************** */
uint8 time_GetTimeInMinutes(void) {
  if(timeSecondsPart>30) {
    return (timeMinutesPart + 1);
  }
  return timeMinutesPart;
}


/** 
 * Returns the seconds portion of the time in the minutes and seconds format.
 * @return The seconds as defined in the description in an unsigned 8 bits
 *         integer
 *************************************************************************** */
uint8 time_GetSecondsPortion(void) {
  return timeSecondsPart;
}


/** 
 * Returns the minutes portion of the time in the minutes and seconds format.
 * @return The minutes as defined in the description in an unsigned 8 bits
 *         integer
 *************************************************************************** */
uint8 time_GetMinutesPortion(void) {
  return timeMinutesPart;
}


/** 
 * Set the current time to the number set in the argument.
 * @param seconds The time to be set in seconds.
 *************************************************************************** */
void time_SetTimeFromSeconds(uint16 seconds) {
  timeInSeconds = seconds;

  /* Convert to minutes+seconds */
  timeSecondsPart = seconds;
  timeMinutesPart = 0;
  while(timeSecondsPart>59) {
    timeMinutesPart++;
    timeSecondsPart -= 60;
  }
  
  /* Check if maximum defined time has been reached */
  if(timeMinutesPart>(maxMinutes-1)) {
    time_End();
  }
}
