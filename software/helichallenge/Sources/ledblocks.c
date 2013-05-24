/**
 * @file ledblocks.h
 * @date 24/05/2013
 * @author: Pawel Kowalski
 *          Carlos Pereira Atencio
 *          
 *************************************************************************** */
#include "ledblocks.h"

/**
 * Description
 *************************************************************************** */
void lb_NorthLightOn(bool newstate) {
  LED_North_PutVal(NULL, newstate);
}


/**
 * Description
 *************************************************************************** */
void lb_SouthLightOn(bool newstate) {
  LED_South_PutVal(NULL, newstate);
}


/**
 * Description
 *************************************************************************** */
void lb_WestLightOn(bool newstate) {
  LED_West_PutVal(NULL, newstate);

}


/**
 * Description
 *************************************************************************** */
void lb_EastLightOn(bool newstate) {
  LED_East_PutVal(NULL, newstate);
}


/**
 * Description
 *************************************************************************** */
void lb_NorthLightToggle() {

}


/**
 * Description
 *************************************************************************** */
void lb_SouthLightToggle() {

}


/**
 * Description
 *************************************************************************** */
void lb_WestLightToggle() {

}


/**
 * Description
 *************************************************************************** */
void lb_EastLightToggle() {

}


/**
 * Description
 *************************************************************************** */
void lb_TestAllLightsIntervaMs(uint16 delay) {
  /* Ensure all off */
  LED_North_PutVal(NULL, FALSE);
  LED_East_PutVal(NULL, FALSE);
  LED_West_PutVal(NULL, FALSE);
  LED_South_PutVal(NULL, FALSE);
  
  /* Turn them ON 1 by 1 with the given delay */
  LED_North_PutVal(NULL, TRUE);
  FRTOS1_vTaskDelay(delay/portTICK_RATE_MS);
  LED_East_PutVal(NULL, TRUE);
  FRTOS1_vTaskDelay(delay/portTICK_RATE_MS);
  LED_West_PutVal(NULL, TRUE);
  FRTOS1_vTaskDelay(delay/portTICK_RATE_MS);
  LED_South_PutVal(NULL, TRUE);
}
