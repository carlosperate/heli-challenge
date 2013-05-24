/**
 * @file ledblocks.h
 * @version 0.1
 * @date 24/05/2013
 * @author: Pawel Kowalski
 *          Carlos Pereira Atencio
 *          
 * Description should go here asap.
 *************************************************************************** */

#ifndef LEDBLOCKS_H_
#define LEDBLOCKS_H_

#include "common.h" 

void lb_NorthLightOn(bool newstate);
void lb_SouthLightOn(bool newstate);
void lb_WestLightOn(bool newstate);
void lb_EastLightOn(bool newstate);
void lb_NorthLightToggle(void);
void lb_SouthLightToggle(void);
void lb_WestLightToggle(void);
void lb_EastLightToggle(void);
void lb_TestAllLightsIntervaMs(uint16 delay);

#endif /* LEDBLOCKS_H_ */
