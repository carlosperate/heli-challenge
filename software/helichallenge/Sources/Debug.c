/*
 * Debug.c
 *
 *  Created on: May 17, 2013
 *      Author: Pawel
 */

#include "Debug.h"
void DebugJoystickADC(){
  AdcRead();
  uart_SendString("X-> ADC: "); uart_SendUInt16(ADC_READOUT[0]);
  uart_SendString("; Srv: ");uart_SendUInt16(js_AdcToUs(ADC_READOUT[0]));
  uart_SendString("\r\nY-> ADC: ");uart_SendUInt16(ADC_READOUT[1]);
  uart_SendString("; Srv: ");uart_SendUInt16(js_AdcToUs(ADC_READOUT[1]));
  uart_SendStringLn("\n"); 
}
void DebugJoystickButtons(){
  bool Value0=Get_Value(0);
  bool Value1=Get_Value(1);
  bool Value2=Get_Value(2);
  bool Value3=Get_Value(3); 
  uart_SendString("Val0:"); uart_SendByte(Value0);
  uart_SendString("; Val1:"); uart_SendByte(Value1);
  uart_SendString("; Val2:"); uart_SendByte(Value2);
  uart_SendString("; Val3:"); uart_SendUInt16(Value3);uart_SendStringLn("\n");
 
}

