/**
 * @file displaycontrol.c
 * @date 12/04/2012
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "displaycontrol.h"


/* Globals local to this file to store the individual digits to display */
byte digit1 = 1;
byte digit2 = 2;
byte digit3 = 3;
byte digit4 = 4;


/** display_Init
 * Function to initialise the I2C IO extender in the display circuit.
 * @param
 * @return
 *************************************************************************** */
void display_Init(void) {
  
}


/** display_SetTime
 * Takes the time to display in seconds, converts it into minutes + seconds 
 * and stores it into the digit globals to be displayed.
 * @param seconds: The time to display in seconds
 *************************************************************************** */
void display_SetTime(uint16 seconds) {
  
}


/** display_SetByte
 * Take a byte positive number and stores its individual digits into the
 * digit globals to be displayed.
 * @param
 *************************************************************************** */
void display_SetByte(byte value) {
  
}


/** display_SetDigit1
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 1
 * @param digit: a unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit1(byte digit) {
  // Remember to sanitise the input, range 0 to 9
}


/** display_SetDigit2
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 2
 * @param digit: a unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit2(byte digit) {
  // Remember to sanitise the input, range 0 to 9
}


/** display_SetDigit3
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 3
 * @param digit: a unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit3(byte digit) {
  // Remember to sanitise the input, range 0 to 9
}


/** display_SetDigit4
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 4
 * @param digit: a unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit4(byte digit) {
  // Remember to sanitise the input, range 0 to 9
}


/** function name
 * Description
 * @param
 *************************************************************************** */
void display_SendI2C() {
  
}


/** display_Flash
 * Flashes the four digits sequentially and then turns all 7segments off.
 * @param
 *************************************************************************** */
void display_FlashAll() {
  display_FlashDigitl();
  display_FlashDigit2();
  display_FlashDigit3();
  display_FlashDigit4();
  //Then remember to turn off all LEDs
  
  /* The following code is only used for testing purposes */
  #ifdef DEBUGFLAG
    uart_SendChar('F');
  #endif
}


/** display_FlashDigit1
 * Description
 * @param
 *************************************************************************** */
void display_FlashDigitl() {
  
}


/** display_FlashDigit2
 * Description
 * @param
 *************************************************************************** */
void display_FlashDigit2() {
  
}


/** display_FlashDigit3
 * Description
 * @param
 *************************************************************************** */
void display_FlashDigit3() {
  
}


/** display_FlashDigit4
 * Description
 * @param
 *************************************************************************** */
void display_FlashDigit4() {
  
}
