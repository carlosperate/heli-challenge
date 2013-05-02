/**
 * @file scheduler.c
 * @date 10/04/2012
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "scheduler.h"
#include "portmacro.h"
#include "application.h"
#include "FRTOS1.h"
#ifdef DEBUGFLAG
  #include "accelerometer.h"
#endif 


/**
 * portTASK_FUNCTION for Task 1
 * Description
 * @param Task1 Name of the task
 *        pvParameters Parameter to pass, not used
 *************************************************************************** */
static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
  	LED_B_Neg();
	FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}


/**
 * portTASK_FUNCTION for Task 2
 * Description
 * @param Task2 Name of the task
 *        pvParameters Parameter to pass, not used
 *************************************************************************** */
static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    #ifdef DEBUGFLAG
        accelerometer_readXYZ();
    #endif 
    LED_R_Neg();
	FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
  }
} 


/**
 * portTASK_FUNCTION for RefreshDisplay
 * This one is meant to flash the 7 segment display at 50hz
 * @param Task3 Name of the task
 *        pvParameters Parameter to pass, not used
 *************************************************************************** */
static portTASK_FUNCTION(RefreshDisplay, pvParameters) {
  /* Set up the parameters for vTaskDelayUntil */
  portTickType xLastWakeTime = xTaskGetTickCount();
  const portTickType xFrequency = 20/portTICK_RATE_MS;
  for(;;) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    schedule50HzAbsolute();
  }
} 


/**
 * portTASK_FUNCTION for OneSecRealTime
 * This function is to be called once a second in a absolute manner.
 * @param OneSecRealTime Name of the task
 *        pvParameters Parameter to pass, not used
 *************************************************************************** */
static portTASK_FUNCTION(OneSecRealTime, pvParameters) {
  (void)pvParameters; /* parameter not used */
  /* Set up the parameters for vTaskDelayUntil */
  portTickType xLastWakeTime = xTaskGetTickCount();
  const portTickType xFrequency = 1000/portTICK_RATE_MS;
  for(;;) {
    /* Wait for the next cycle */
    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    LED_G_Neg();
    uint16 printout = js_Move();
    uart_SendStringLn((unsigned char*)"Y microseconds:");
    uart_SendInt16(printout);
    uart_SendStringLn((unsigned char*)"\n");
    FRTOS1_vTaskDelay(2500/portTICK_RATE_MS);

    schedule1HzAbsolute();
  }
} 


/**
 * Description
 *************************************************************************** */
void createTasks() {
  if (FRTOS1_xTaskCreate(
	    Task1,                      /* pointer to the task */
	    (signed portCHAR *)"Task1", /* task name for kernel awareness debugging */
	    configMINIMAL_STACK_SIZE,   /* task stack size */
	    (void*)NULL,                /* optional task startup argument */
	    tskIDLE_PRIORITY,           /* initial priority */
	    (xTaskHandle*)NULL          /* optional task handle to create */
	  ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
      Task2,                      /* pointer to the task */
      (signed portCHAR *)"Task2", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE,   /* task stack size */
      (void*)NULL,                /* optional task startup argument */
      tskIDLE_PRIORITY,           /* initial priority */
      (xTaskHandle*)NULL          /* optional task handle to create */
    ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  } 
  if (FRTOS1_xTaskCreate(
      RefreshDisplay,              /* pointer to the task */
      (signed portCHAR *)"RefreshDisplay", /* task name */
      configMINIMAL_STACK_SIZE,   /* task stack size */
      (void*)NULL,                /* optional task startup argument */
      tskIDLE_PRIORITY,           /* initial priority */
      (xTaskHandle*)NULL          /* optional task handle to create */
    ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  } 
  if (FRTOS1_xTaskCreate(
      OneSecRealTime,             /* pointer to the task */
      (signed portCHAR *)"OneSecRealTime", /* task name */
      configMINIMAL_STACK_SIZE,   /* task stack size */
      (void*)NULL,                /* optional task startup argument */
      tskIDLE_PRIORITY,           /* initial priority */
      (xTaskHandle*)NULL          /* optional task handle to create */
    ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  } 
}

