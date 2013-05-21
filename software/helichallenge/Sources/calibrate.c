/*
 * calibrate.c
 *
 *  Created on: May 10, 2013
 *      Author: Pawel
 */
#include "calibrate.h"


InitialRead(void){
  AdcRead();
  CalibrationCentreX=ADC_READOUT[0];
  CalibrationCentreY=ADC_READOUT[1];  
  CalibrationLeft=ADC_READOUT[0];
  CalibrationUp=ADC_READOUT[1];  
  CalibrationRight=ADC_READOUT[0];
  CalibrationDown=ADC_READOUT[1];
  CalibrationDeadLeft=ADC_READOUT[0];
  CalibrationDeadUp=ADC_READOUT[1];
  CalibrationDeadRight=ADC_READOUT[0];
  CalibrationDeadDown=ADC_READOUT[1];
  uart_SendInt16(CalibrationLeft);uart_SendStringLn("\n");
  uart_SendInt16(CalibrationRight);uart_SendStringLn("\n");
  uart_SendInt16(CalibrationUp);uart_SendStringLn("\n");
  uart_SendInt16(CalibrationDown);uart_SendStringLn("\n");
}
ContinuousRead(void){
  //for(;;){
  AdcRead();
  //Get maxima and minima for ADC values over a period of time
  if (ADC_READOUT[0]<CalibrationLeft){CalibrationLeft=ADC_READOUT[0];}
  if (ADC_READOUT[0]>CalibrationRight){CalibrationRight=ADC_READOUT[0];}
  if (ADC_READOUT[1]<CalibrationDown){CalibrationDown=ADC_READOUT[1];}
  if (ADC_READOUT[1]>CalibrationUp){CalibrationUp=ADC_READOUT[1];}
  //if (Get_Value(1)==0){CalibrationState++;break;};
  //} 
}
StaticRead(void){
  AdcRead();
  CalibrationCentreX=((ADC_READOUT[0]+CalibrationCentreX)/2);
  CalibrationCentreY=((ADC_READOUT[1]+CalibrationCentreY)/2);
  if (ADC_READOUT[0]<CalibrationDeadLeft){CalibrationDeadLeft=ADC_READOUT[0];}
  if (ADC_READOUT[0]>CalibrationDeadRight){CalibrationDeadRight=ADC_READOUT[0];}
  if (ADC_READOUT[1]<CalibrationDeadDown){CalibrationDeadDown=ADC_READOUT[1];}
  if (ADC_READOUT[1]>CalibrationDeadUp){CalibrationDeadUp=ADC_READOUT[1];}

}
calibration (void){
  LED_North_PutVal(NULL,1);
  InitialRead();
  LED_East_PutVal(NULL,1);
  for(;;){
  ContinuousRead();
  if (Get_Value(1)==0){break;};}
  LED_South_PutVal(NULL,1);
  for(;;){
  StaticRead();
  if (Get_Value(1)==0){break;};}
  LED_North_PutVal(NULL,0);
  LED_East_PutVal(NULL,0);
  LED_South_PutVal(NULL,0);
}

