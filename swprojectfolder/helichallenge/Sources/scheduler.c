/**
 * @file scheduler.c
 * @date 10/04/2012
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "scheduler.h"
#include "portmacro.h"
#include "FRTOS1.h"
#include "accelerometer.h"


/** portTASK_FUNCTION for Task 1
 * Description
 * @param
 * @return
 *************************************************************************** */
static portTASK_FUNCTION(Task1, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
  	LED_B_Neg();
	FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  }
}


/** portTASK_FUNCTION for Task 2
 * Description
 * @param
 * @return
 *************************************************************************** */
static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    accelerometer_readXYZ();
    LED_R_Neg();
	FRTOS1_vTaskDelay(2000/portTICK_RATE_MS);
  }
} 


/** portTASK_FUNCTION for Task 3
 * This one is meant to flash the 7 segment display at 50hz
 * @param
 * @return
 *************************************************************************** */
static portTASK_FUNCTION(Task3, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    //display_FlashAll();
    uart_SendStringLn((unsigned char*)"Task3");
    FRTOS1_vTaskDelay(1500/portTICK_RATE_MS);
  }
} 


/** portTASK_FUNCTION for Task 4
 * Description
 * @param
 * @return
 *************************************************************************** */
static portTASK_FUNCTION(Task4, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    LED_G_Neg();
    uart_SendStringLn((unsigned char*)"Task4");
    FRTOS1_vTaskDelay(2500/portTICK_RATE_MS);
  }
} 



/** createTasks
 * Description
 * @param
 * @return
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
      Task3,                      /* pointer to the task */
      (signed portCHAR *)"Task3", /* task name for kernel awareness debugging */
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
      Task4,                      /* pointer to the task */
      (signed portCHAR *)"Task3", /* task name for kernel awareness debugging */
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

