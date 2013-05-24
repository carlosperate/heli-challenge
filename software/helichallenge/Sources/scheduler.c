/**
 * @file scheduler.c
 * @date 02/05/2013
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "scheduler.h"
#include "application.h"
#include "portmacro.h"
#include "FRTOS1.h"
#include "accelerometer.h"
#include "joystick_button.h"
#include "Button_LED_Test.h"



/**
 * portTASK_FUNCTION for task20HzRelative
 * This is the main function of the application where the state machine and
 * all operational code will be executed.
 * @param task20HzRelative Name of the task
 *        pvParameters Parameter to pass, not used
 *************************************************************************** */
static portTASK_FUNCTION(task20HzRelative, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    schedule20HzRelative();
	FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
  }
}


/**
 * portTASK_FUNCTION for task50HzAbsolute
 * This one is meant to flash the 7 segment display at 50hz
 * @param task50HzAbsolute Name of the task
 *        pvParameters Parameter to pass, not used
 *************************************************************************** */
static portTASK_FUNCTION(task250HzAbsolute, pvParameters) {
  (void)pvParameters; /* parameter not used */
  /* Set up the parameters for vTaskDelayUntil */
  //portTickType xLastWakeTime = xTaskGetTickCount();
  //const portTickType xFrequency = 4/portTICK_RATE_MS;
  for(;;) {
    /* Wait for the next cycle */
    //vTaskDelayUntil(&xLastWakeTime, xFrequency);
    schedule250HzAbsolute();
    FRTOS1_vTaskDelay(3/portTICK_RATE_MS);
  }
} 


/**
 * portTASK_FUNCTION for task1HzAbsolute
 * This function is to be called once a second in a absolute manner.
 * @param task1HzAbsolute Name of the task
 *        pvParameters Parameter to pass, not used
 *************************************************************************** */
static portTASK_FUNCTION(task1HzAbsolute, pvParameters) {
  (void)pvParameters; /* parameter not used */
  /* Set up the parameters for vTaskDelayUntil */
  portTickType xLastWakeTime = xTaskGetTickCount();
  const portTickType xFrequency = 1000/portTICK_RATE_MS;
  for(;;) {
    /* Wait for the next cycle */
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    schedule1HzAbsolute();
  }
} 


/**
 * Creates and assigns the tasks to the RTOS.
 *************************************************************************** */
void createTasks() {
  if (FRTOS1_xTaskCreate(
      task20HzRelative,           /* pointer to the task */
      (signed portCHAR *)"task20HzRelative", /* task name */
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
      task250HzAbsolute,           /* pointer to the task */
      (signed portCHAR *)"task250HzAbsolute", /* task name */
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
      task1HzAbsolute,             /* pointer to the task */
      (signed portCHAR *)"task1HzAbsolute", /* task name */
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
