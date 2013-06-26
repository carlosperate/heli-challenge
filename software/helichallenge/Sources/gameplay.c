/**
 * @file gameplay.c
 *
 **************************************************************************** */
#include "gameplay.h"
#include "joystick.h"
#include "servocontrol.h"
#include "timecontrol.h"
#include "ledblocks.h"


/* Local globals */
static uint8 difficultyLevel = 0;
static int16 xOffset = 0;
static int16 yOffset = 0;
static int8 xSine = 0;
static bool isXCrescendo = TRUE;
static int8 yCosine = 64;
static bool isYCrescendo = TRUE;


/* Private functions*/
void gp_CalculateDifficultyLevel(void);
void gp_CalculateDifficultyOffsets(void);
void gp_CalculateWaveOffsets(void);
void gp_CalculateDifficultyLevel(void);


/**
 * Description
 *************************************************************************** */
void gp_Play(void) {
  /* These two functions populate the globals with the offsets for X and Y */
  gp_CalculateDifficultyLevel();
  gp_CalculateDifficultyOffsets();
  
  /* Getting joystick input converted to a number between 0 and 2^16, and adding
   * the offset due to difficulty levels */
  int32 y16BitRangeIn32BitVar = servo_16BitsToUs(joystick_GetY()) + yOffset;
  int32 x16BitRangeIn32BitVar = servo_16BitsToUs(joystick_GetX()) + xOffset;
  
  /* Adding an additional rotating continuous movement */
//  if(difficultyLevel>0) {
//    yUs += yCosine;
//    xUs += xSine;
//  }
  
  /* Sanitising data for out of range values */
  uint16 y16BitRange;
  uint16 x16BitRange;
  if(y16BitRangeIn32BitVar<0) {
    y16BitRange = 0;
  } else if(y16BitRangeIn32BitVar>65535) {
    y16BitRange = 65535;
  } else {
    y16BitRange = (uint16)y16BitRangeIn32BitVar;
  }
  
  if(x16BitRangeIn32BitVar < 0) {
    x16BitRange = 0;
  } else if(x16BitRangeIn32BitVar > 65535) {
    x16BitRange = 65535;
  } else {
    x16BitRange = (uint16)x16BitRangeIn32BitVar;
  }
  
  /* Sending the data to the servo module */
  servo_Duty16BitY(y16BitRange);
  servo_Duty16BitX(x16BitRange);
}


/**
 * Description
 * @param joystickOp
 * @return
 *************************************************************************** */
void gp_CalculateDifficultyOffsets(void) {
  switch(difficultyLevel) {
    case 0:  // Nothing happens here
      lb_AllLedsOff();
      xOffset = 0;
      yOffset = 0;
      break;
    case 1:  // North wind, affects Y
    //case7:
      lb_AllLedsOff();
      lb_NorthLightOn(TRUE);
      yOffset = -275;
      xOffset = 0;
      break;
    case 2:  // East wind, affects X
    //case 8:
      lb_AllLedsOff();
      lb_EastLightOn(TRUE);
      xOffset += 275;
      yOffset = 0;
      break;
    case 3:  // South wind, affects Y
    //case 9:
      lb_AllLedsOff();
      lb_SouthLightOn(TRUE);
      yOffset = 225;
      xOffset = 0;
      break;
    case 4:  // West wind, affects X
    //case 10:
      lb_AllLedsOff();
      lb_WestLightOn(TRUE);
      xOffset = -225;
      yOffset = 0;
      break;
    case 5:  // North & East, affects X & Y
    //case 11:
      lb_AllLedsOff();
      lb_EastLightOn(TRUE);
      lb_NorthLightOn(TRUE);
      xOffset = 275;
      yOffset = 275;
      break;
    case 6:  // South & West, affects X & Y
    //case 12:
      lb_AllLedsOff();
      lb_WestLightOn(TRUE);
      lb_SouthLightOn(TRUE);
      yOffset = 225;
      xOffset = -225;
      break;
    default:
      lb_AllLedsOff();
      xOffset = 0;
      yOffset = 0;
      break;
  }
}


/**
 * For now the waveforms will be triangular waves.
 *************************************************************************** */
void gp_CalculateWaveOffsets(void) {
  if(isXCrescendo ==  TRUE) {
    xSine++;
    if(xSine==127) isXCrescendo = FALSE;
  } else {
    xSine--;
    if(xSine==-128) isXCrescendo = TRUE;
  }
  
  if(isYCrescendo ==  TRUE) {
    yCosine++;
    if(yCosine==127) isYCrescendo = FALSE;
  } else {
    yCosine--;
    if(yCosine==-128) isYCrescendo = TRUE;
  }
}


/**
 * This function sets the difficulty level (a static global of this module) of
 * the game based on how long the user has been playing.
 * Makes a call to the "timecontrol.h" module.
 * The constant DIFFICULTY_TIME_SPLIT is defined here because it is highly 
 * dependent of the algorithm used to determine the difficulty level and it 
 * needs to be visible to readability.
 *************************************************************************** */
static const uint8 DIFFICULTY_TIME_SPLIT = 20;
void gp_CalculateDifficultyLevel(void) {
  /* Different approach based on user testing. First 30 seconds without any
   * additional wind. After that wind changes every 20 seconds. */
  if(time_GetTimeInSeconds() < 30) {
    difficultyLevel = 0;
  } else {
    difficultyLevel =
        (uint8)((time_GetTimeInSeconds() - 10) / DIFFICULTY_TIME_SPLIT);
  }
}


/**
 * @return The current difficulty level.
 *************************************************************************** */
uint8 gp_GetDifficultyLevel(void) {
  return difficultyLevel;
}
