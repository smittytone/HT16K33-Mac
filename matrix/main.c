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

        // ...and issue passed in commands/data
        return matrix_commands(argc - 2, argv + 2);
    }
}


int matrix_commands(int argc, char *argv[]) {
    for (int i = 0 ; i < argc ; ++i) {
        char *token = argv[i];

        if (token[0] == '-') {
            switch (token[1]) {
                case 'a':   // ACTIVATE OR DEACTIVATE DISPLAY
                    {   
                        bool is_on = true;
                        
                        if (i < argc - 1) {
                            token = argv[++i];
                            if (strlen(token) == 1) {
                                is_on = (strcmp(token, "0") != 0);
                            } else {
                                is_on = (strcmp(token, "off") != 0);
                            }
                        }

                        if (is_on) {
                            HT16K33_init(0);
                        } else {
                            HT16K33_write_cmd(HT16K33_CMD_DISPLAY_OFF);
                            HT16K33_write_cmd(HT16K33_CMD_POWER_OFF);    
                        }
                    }
                    break;

                case 'b':   // SET BRIGHTNESS
                    {
                        token = argv[++i];
                        u_int8_t brightness = (uint8_t)strtol(token, NULL, 0);
                        if (brightness > 15) {
                            print_error("Brightness value out of range (0-15)");
                            return 1;
                        }
                        HT16K33_set_brightness(brightness);
                    }
                    break;
                
                case 'c':   // DISPLAY CHARACTER
                    {
                        token = argv[++i];
                        uint8_t ascii = (uint8_t)strtol(token, NULL, 0);
                        if (ascii < 32 || ascii > 127) {
                            print_error("Ascii value out of range (32-127)");
                            return 1;
                        }

                        bool do_centre = false;
                        if (i < argc - 1) {
                            token = argv[++i];
                            if (strlen(token) == 1) {
                                do_centre = (strcmp(token, "1") == 0);
                            } else {
                                do_centre = (strcmp(token, "true") == 0);
                            }
                        }

                        HT16K33_set_char(ascii, do_centre);
                        HT16K33_draw();                    
                    }
                    break;

                case 'p':   // PLOT A POINT
                    {
                        token = argv[++i];
                        int x = strtol(token, NULL, 0);

                        token = argv[++i];
                        int y = strtol(token, NULL, 0);

                        if (x < 0 || x > 7 || y < 0 || y > 7) {
                            print_error("Co-ordinate out of range (0-7)");
                            return 1;
                        }

                        int ink = 1;
                        if (i < argc - 1) {
                            token = argv[++i];
                            ink = strtol(token, NULL, 0);
                            if (ink != 1 && ink != 0) ink = 1;
                        }

                        HT16K33_plot((uint8_t)x, (uint8_t)y, ink == 1);
                        HT16K33_draw(); 
                    }
                    break;

                default:
                    // ERROR
                    print_error("Unknown command");
                    return 1;
            }
        }

    }
    
    return 0;
}


void print_error(char* msg) {
    fprintf(stderr, "[ERROR] %s\n", msg);
}