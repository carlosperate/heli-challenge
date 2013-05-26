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

inline void lb_NorthLightOn(bool newstate);
inline void lb_SouthLightOn(bool newstate);
inline void lb_WestLightOn(bool newstate);
inline void lb_EastLightOn(bool newstate);
inline void lb_AllLedsOn(void);
inline void lb_AllLedsOff(void);
void lb_NorthLightToggle(void);
void lb_SouthLightToggle(void);
void lb_WestLightToggle(void);
void lb_EastLightToggle(void);
void lb_TestAllLightsIntervalMs(uint16 delay);

#endif /* LEDBLOCKS_H_ */
