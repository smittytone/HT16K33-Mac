/**
 *
 * I2C driver w. HT16K33
 * Version 1.0.0
 * Copyright © 2019, James Bowan; 2022, smittytone
 * Licence: BSD 3-Claus
 *
 */
#include "main.h"


I2CDriver i2c;

int main(int argc, char *argv[]) {

    // Process arguments
    if (argc < 2) {
        // Insufficient args -- bail
        printf("Usage: i2ccl <DEVICE_PATH> <commands>\n");
        exit(1);
    } else {
        // Connect...
        i2c_connect(&i2c, argv[1]);
        if (!i2c.connected) exit(1);

        // ...and issue passed in commands/data
        return i2c_commands(&i2c, argc - 2, argv + 2);
    }
}
