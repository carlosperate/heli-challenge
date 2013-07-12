/*
 * debug.c
 *
 *  Created on: May 17, 2013
 *      Author: Pawel
 */

#include "debug.h"
#include "joystick.h"
#include "gameplay.h"
#include "servocontrol.h"
#include "ledblocks.h"
#include "uartcontrol.h"


static uint8 ledTestCounter=0;

/**
 * Description
 *************************************************************************** */
void debug_AdcXYServo(void) {
#ifdef DEBUGFLAG
  //TODO: reading servo here, refactor to reduce cohersion
  AdcRead();
  uint16 xData = ADC_READOUT[0];
  uint16 yData = ADC_READOUT[1];
  //uart_SendChar(27); //ESC command
  //uart_SendString("[H"); //Return to begging of line
  uart_SendString("X-> ADC: ");
  uart_SendUInt16(xData);
  uart_SendString(", ");
  xData = joystick_GetX();
  uart_SendUInt16(xData);
  uart_SendString("; Srv: "); 
  uart_SendUInt16(servo_16BitsToUs(xData));
  uart_SendString("\r\nY-> ADC: ");
  uart_SendUInt16(yData);
  uart_SendString(", ");
  yData = joystick_GetY();
  uart_SendUInt16(yData);
  uart_SendString("; Srv: ");
  uart_SendUInt16(servo_16BitsToUs(yData));
  uart_SendString("\r\n"); 
#endif
}


/**
 * Description
 *************************************************************************** */
void debug_PlayData(void) { 
  uart_SendString("\r\nPlay Difficulty: ");
  uart_SendByte(gp_GetDifficultyLevel());
  uart_SendString("\r\n"); 
  debug_AdcXYServo();
}

/**
 * Description
 *************************************************************************** */
void debug_Buttons(void) { 
#ifdef DEBUGFLAG
  uart_SendString("Buttons:");
  uart_SendByte(joystick_isButtonPressed(Button_Trigger));
  uart_SendString("; "); 
  uart_SendByte(joystick_isButtonPressed(Button_Centre));
  uart_SendString("; "); 
  uart_SendByte(joystick_isButtonPressed(Button_Left));
  uart_SendString("; ");
  uart_SendByte(joystick_isButtonPressed(Button_Right));
  uart_SendString("; Box: ");
  uart_SendByte(joystick_isButtonPressed(Button_Box));
  uart_SendString("\r\n");
#endif
}


/**
 * Description
 *************************************************************************** */
void debug_JoystickServo(void) {
#ifdef DEBUGFLAG
  debug_AdcXYServo();
  debug_Buttons();
  uart_SendString("\r\n");
#endif
}


/**
 * Description
 *************************************************************************** */
bool debug_Leds(void) {
  bool continuetest = TRUE;
  FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  
  /* Add to the counter with a button pressed */
  if(joystick_isButtonPressed(Button_Centre)) {
    ledTestCounter++;
  }
  
  /* Based on counter turn on only one LED block */
  if(ledTestCounter == 0 ) {
    uart_SendStringLn("LED test");
  } else if(ledTestCounter == 1) {
    uart_SendStringLn("North");
    lb_NorthLightOn(TRUE);  
  } else if(ledTestCounter == 2) {
    uart_SendStringLn("South");
    lb_NorthLightOn(FALSE);
    lb_SouthLightOn(TRUE);
  } else if(ledTestCounter == 3) {
    uart_SendStringLn("East");
    lb_SouthLightOn(FALSE);
    lb_WestLightOn(TRUE);
  } else if(ledTestCounter == 4) {
    uart_SendStringLn("West");
    lb_WestLightOn(FALSE);
    lb_EastLightOn(TRUE);
  } else {
    lb_EastLightOn(FALSE);
    ledTestCounter = 0;
    continuetest = FALSE;
  }
  
  return continuetest;
}
