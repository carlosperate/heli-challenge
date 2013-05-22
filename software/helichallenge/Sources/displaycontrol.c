/**
 * @file displaycontrol.c
 * @date 06/05/2013
 * @author: Carlos Pereira Atencio
 **************************************************************************** */
#include "displaycontrol.h"


/* Constants I2C IO extender for the display subsystem */
const static uint8 DISPLAY_ADDRESS_WRITE  = 0x20;
const static uint8 DISPLAY_ADDRESS_READ   = 0x20;
const static uint8 DISPLAY_REGISTER_START = 0x00;
const static uint8 DISPLAY_REGISTER_OPSET = 0x09;

/* Globals local to this file to store the individual digits to display */
static uint8 digit1 = 1;
static uint8 digit2 = 2;
static uint8 digit3 = 3;
static uint8 digit4 = 4;
static uint8 turn = 0;


/* Local functions */
void display_SendI2CByte(uint8 byteToSend);


/**
 * Initialises the I2C IO extender in the display circuit.
 *************************************************************************** */
void display_Init(void) {
  #ifdef DISPLAY_CONNECTED
    uint8 registerPointer = DISPLAY_REGISTER_START;
    uint8 registerConf[6] = {
        0x00,     /** IODIR:  All outputs. */
        0x00,     /** IPOL: All GPIO will reflect the same logic as input pin. */
        0x00,     /** GPINTEN: Disable all input interrupts. */
        0x00,     /** DEFVA: Interrupt state trigger, not active. */
        0x00,     /** INTCON: Int. compare against previous value (not used). */
        0x2A};    /** IOCON: Disable sequential operation */
    
    if ( GI2C1_WriteAddress(DISPLAY_ADDRESS_READ, &registerPointer,
        1, registerConf, 6) != ERR_OK) {
      //Do something for error checking 
    }
  #endif
}


/**
 * Description
 * @param byteToSend A byte, to represent the IO expander outputs to be 
 *                   sent by I2C.
 *************************************************************************** */
void display_SendI2CByte(uint8 byteToSend) {
  #ifdef DISPLAY_CONNECTED
    uint8 registerPointer = DISPLAY_REGISTER_OPSET;
    if ( GI2C1_WriteAddress(DISPLAY_ADDRESS_READ, &registerPointer,
        1, &byteToSend, 1) != ERR_OK ) {
      //Do something for error checking 
    }
  #endif
}


/**
 * Description
 * @param value A 16 bits unsigned integer, to to be displayed in the 4 digit
 *              seven segment.
 *************************************************************************** */
void display_SetUint16(uint16 value) {
  /* Break down 'value' into digits starting with the least significant */
  display_SetDigit1(value%10);
  value/=10;
  display_SetDigit2(value%10);
  value/=10;
  display_SetDigit3(value%10);
  if(value>100) {
    value/=10;
    display_SetDigit4(value%10);
  } else {
    display_SetDigit4(value/10);
  }
}



/**
 * Takes the time to display in seconds, converts it into minutes + seconds 
 * and stores it into the digit globals to be displayed.
 * @param value An 8 bits unsigned integer, to to be displayed in the two
 *              leftmost digits in the 4-digit-seven-segment.
 *************************************************************************** */
void display_SetByteLeft(uint8 value) {
  /* Break down 'value' into digits starting with the least significant */
  display_SetDigit3(value%10);
  if(value>100) {
    value/=10;
    display_SetDigit4(value%10);
  } else {
    display_SetDigit4(value/10);
  }
}


/**
 * Take a byte of value up to 99 and stores its individual digits into the
 * digit globals to be displayed.
 * @param value An 8 bits unsigned integer, to to be displayed in the two
 *              rightmost digits in the 4-digit-seven-segment.
 *************************************************************************** */
void display_SetByteRight(uint8 value) {
  /* Break down 'value' into digits starting with the least significant */
  display_SetDigit1(value%10);
  if(value>100) {
    value/=10;
    display_SetDigit2(value%10);
  } else {
    display_SetDigit2(value/10);
  }
}


/**
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 1
 * @param digit A unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit1(uint8 digit) {
  /* Sanitise input to only take one digit using integer multiplication */
  while(digit>9) {
    digit -= ((uint8)digit/(uint8)10) * (uint8)10; 
  }
  digit1 = digit;
}


/**
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 2
 * @param digit A unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit2(uint8 digit) {
  /* Sanitise input to only take one digit using integer multiplication */
  while(digit>9) {
    digit -= ((uint8)digit/(uint8)10) * (uint8)10; 
  }
  digit2 = digit;
}


/**
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 3
 * @param digit A unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit3(uint8 digit) {
  /* Sanitise input to only take one digit using integer multiplication */
  while(digit>9) {
    digit -= ((uint8)digit/(uint8)10) * (uint8)10; 
  }
  digit3 = digit;
}


/**
 * Takes a number from 0 to 9 and saves it into the global variable for digit
 * 4
 * @param digit A unsigned char with a value 0 to 9
 *************************************************************************** */
void display_SetDigit4(uint8 digit) {
  /* Sanitise input to only take one digit using integer multiplication */
  while(digit>9) {
    digit -= ((uint8)digit/(uint8)10) * (uint8)10; 
  }
  digit4 = digit;
}


/**
 * Description
 *************************************************************************** */
void display_DisplayDigitl(void) {
  display_SendI2CByte((digit1&0b00001111)|0b00010000);
}


/**
 * Description
 *************************************************************************** */
void display_DisplayDigit2(void) {
  display_SendI2CByte((digit2&0b00001111)|0b00100000); 
}


/**
 * Description
 *************************************************************************** */
void display_DisplayDigit3(void) {
  display_SendI2CByte((digit3&0b00001111)|0b01000000);
}


/**
 * Description
 *************************************************************************** */
void display_DisplayDigit4(void) {
  display_SendI2CByte((digit4&0b00001111)|0b10000000);
}


/**
 * Description
 *************************************************************************** */
void display_AllDigitsOff(void) {
  display_SendI2CByte(0x00);
}


/**
 * Flashes the four digits sequentially and then turns all 7segments off.
 *************************************************************************** */
void display_FlashAllDigits(void) {
  turn++;
  switch(turn) {
    case 1:
      display_DisplayDigitl();
      break;
    case 2:
      display_DisplayDigit2();
      break;
    case 3:
      display_DisplayDigit3();
      break;
    case 4:
      display_DisplayDigit4();
      // no break to reset turn
    default:
      turn=0;
      break;
  }
  //display_AllDigitsOff();
}
