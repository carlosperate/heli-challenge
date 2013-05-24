/*
 * Button_LED_Test.c
 *
 *  Created on: May 3, 2013
 *      Author: Pawel Kowalski
 */

#include "Button_LED_Test.h"

void TestLEDs(void) {
  bool Value0=TRUE;//Get_Value(0);
  bool Value1=TRUE;//Get_Value(1);
  bool Value2=TRUE;//Get_Value(2);
  bool Value3=TRUE;//Get_Value(3);
  LED_North_PutVal(NULL,Value0);
  LED_East_PutVal(NULL,Value1);
  LED_West_PutVal(NULL,Value2);
  LED_South_PutVal(NULL,Value3);
}

