#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

#include "application.h"

const int BOARD_LED = D7;
const int ANALOG_MAX = 4095;
const double ANALOG_RES = 0.0008;

// Limitations
const int MAX_PUBLISH_LENGTH = 255;
const int MAX_VARIABLE_LENGTH = 622;
const int MAX_NAME_LENGTH = 12;

// Other Limits
const int MAX_NUM_VARIABLES = 20;

#endif