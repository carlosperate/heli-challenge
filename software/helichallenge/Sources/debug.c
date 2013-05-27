/*
 * debug.c
 *
 *  Created on: May 17, 2013
 *      Author: Pawel
 */

#include "debug.h"
#include "joystick.h"
#include "joystickservo.h"
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
  uart_SendString("X-> ADC: ");
  uart_SendUInt16(ADC_READOUT[0]);
  uart_SendString(", ");
  uart_SendUInt16(joystick_GetX());
  uart_SendString("; Srv: "); 
  uart_SendUInt16(js_GetXUs());
  uart_SendString("\r\nY-> ADC: ");
  uart_SendUInt16(ADC_READOUT[1]);
  uart_SendString(", ");
  uart_SendUInt16(joystick_GetY());
  uart_SendString("; Srv: ");
  uart_SendUInt16(js_GetYUs());
  uart_SendString("\r\n"); 
#endif
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