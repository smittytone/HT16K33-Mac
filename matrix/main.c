/**
 *
 * I2C driver w. HT16K33
 * Version 1.0.0
 * Copyright © 2022, smittytone
 * Licence: MIT
 *
 */
#include "main.h"


I2CDriver i2c;

int main(int argc, char *argv[]) {

    // Process arguments
    if (argc < 2) {
        // Insufficient args -- bail
        printf("Usage: matrix <DEVICE_PATH> <commands>\n");
        exit(1);
    } else {
        // Connect...
        // ...arg #1 is the device path
        i2c_connect(&i2c, argv[1]);
        if (!i2c.connected) exit(1);

        HT16K33_init(0);

        // ...and issue passed in commands/data
        return matrix_commands(argc - 2, argv + 2);
    }
}


int matrix_commands(int argc, char *argv[]) {
    for (int i = 0 ; i < argc ; ++i) {
        char *token = argv[i];

    }

    return 1;
}