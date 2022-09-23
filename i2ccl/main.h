/**
 *
 * I2C driver w. HT16K33
 * Version 1.0.0
 * Copyright © 2019, James Bowan; 2022, smittytone
 * Licence: MIT
 *
 */
#ifndef _MAIN_H_
#define _MAIN_H_


/*
 * INCLUDES
 */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <assert.h>
#include <memory.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <IOKit/serial/ioss.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>


// App includes
#include "i2cdriver.h"


#endif      // _MAIN_H_
