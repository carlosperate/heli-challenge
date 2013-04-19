#include "application.h"


/** initialiseAll
 * Function call to initialise all the components used in this application.
 * It currently contains initialisation calls for: UART.
 *************************************************************************** */
void initialiseAll(void) {
  uart_Init();
  GI2C1_Init();
}


