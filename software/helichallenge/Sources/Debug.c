/*
 * Debug.c
 *
 *  Created on: May 17, 2013
 *      Author: Pawel
 */

#include "Debug.h"
void DebugJoystickADC(){
 AdcRead();
 uart_SendStringLn("X:"); uart_SendUInt16(ADC_READOUT[0]);uart_SendStringLn("\n"); 
 uart_SendStringLn("Y:");uart_SendUInt16(ADC_READOUT[1]);uart_SendStringLn("\n"); 
}
void DebugJoystickButtons(){
  bool Value0=Get_Value(0);
  bool Value1=Get_Value(1);
  bool Value2=Get_Value(2);
  bool Value3=Get_Value(3); 
  uart_SendStringLn("Value0:"); uart_SendUInt16(Value0);uart_SendStringLn("\n");
  uart_SendStringLn("Value1:"); uart_SendUInt16(Value1);uart_SendStringLn("\n");
  uart_SendStringLn("Value2:"); uart_SendUInt16(Value2);uart_SendStringLn("\n");
  uart_SendStringLn("Value3:"); uart_SendUInt16(Value3);uart_SendStringLn("\n");
 
}

