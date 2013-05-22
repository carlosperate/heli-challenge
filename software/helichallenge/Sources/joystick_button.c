/*
 * joystick_button.c
 *
 *  Created on: Apr 27, 2013
 *      Author: Pawel Kowalski
 */

#include "joystick_button.h"
bool Get_Value(uint16 SignalName){
  bool Value;
  if (SignalName==0){
    Value=Joystick0_GetVal(NULL);
  };
  if (SignalName==1){
    Value=Joystick1_GetVal(NULL);
  };
  if (SignalName==2){
    Value=Joystick2_GetVal(NULL);
  };
  if (SignalName==3){
    Value=Joystick3_GetVal(NULL);
  };
  return Value;
}




