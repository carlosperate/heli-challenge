/**
 * @file uartcontrol.c
 * @date 02/05/2013
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include <stdio.h>
#include "uartcontrol.h"


/** Global to this file to contain the UART handle */
static UART_handler deviceData;


/**
 * Initialises the UART handle to be able to control the UART internal
 * peripheral.
 *************************************************************************** */
void uart_Init(void) {
  deviceData.handle = AS1_Init(&deviceData);
  deviceData.isSent = FALSE;
}


/**
 * Sends a single character to the UART peripheral.
 * @param ch The character to send
 *************************************************************************** */
void uart_SendChar(char ch) {
  deviceData.isSent = FALSE;  // reset flag
  while(AS1_SendBlock(deviceData.handle, (LDD_TData*)&ch, 1)!= ERR_OK) {}
  while(!deviceData.isSent) {} // wait until we get the block has been sent 
}


/** 
 * Sends a full string to the UART peripheral.
 * To do so, it sends concatenated characters in a string to the 
 * Uart_SendChar function until the end of the string is reached.
 * @param str A Null terminated string of text
 *************************************************************************** */
void uart_SendString(const char *str) {
  while(*str!='\0') {
    uart_SendChar(*str++);
  }
}

/**
 * Sends a full string to the UART peripheral and attaches a break line.
 * To do so, it sends concatenated characters in a string to the 
 * Uart_SendChar function until the end of the string is reached.
 * @param str A Null terminated string of text
 *************************************************************************** */
void uart_SendStringLn(const char *str) {
  uart_SendString(str);
  uart_SendString("\r\n");
}


/** 
 * Sends a byte (unsigned 8 bit integer) to the UART peripheral.
 * @param integer Number to convert to text and send to the UART peripheral
 *************************************************************************** */
void uart_SendByte(const uint8 integer) {
  char numbstr[4];
  sprintf(numbstr, "%u", integer);
  uart_SendString(numbstr);
}


/** uart_SendInt8
 * Sends a signed 8 bit integer to the UART peripheral.
 * @param integer Number to convert to text and send to the UART peripheral
 *************************************************************************** */
void uart_SendInt8(const int8 integer) {
  char numbstr[5];
  sprintf(numbstr, "%d", integer);
  uart_SendString(numbstr);
}


/**
 * Sends a signed 16 bit integer to the UART peripheral.
 * @param integer Number to convert to text and send to the UART peripheral
 *************************************************************************** */
void uart_SendInt16(const int16 integer) {
  char numbstr[7];
  sprintf(numbstr, "%d", integer);
  uart_SendString(numbstr);
}


/**
 * Sends a signed 32 bit integer to the UART peripheral.
 * @param integer Number to convert to text and send to the UART peripheral
 *************************************************************************** */
void uart_SendInt32(const int32 integer) {
  char numbstr[12];
  sprintf(numbstr, "%d", integer);
  uart_SendString(numbstr);
}


/**
 * Sends a float to the UART peripheral.
 * @param floatnumber Number to convert to text and send to the UART
 * peripheral
 *************************************************************************** */
void uart_SendFloat(const float floatnumber) {
  char numbstr[32];
  sprintf(numbstr, "%f", floatnumber);
  uart_SendString(numbstr);
}
