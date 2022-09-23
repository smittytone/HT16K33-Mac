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
int i2c_address = HT16K33_I2C_ADDR;


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

        // Check for an alternative I2C address
        if (argc > 2) {
            char* token = argv[2];
            if (token[0] != '-') {
                // Not a command, so an address
                i2c_address = strtol(token, NULL, 0);
                
                if (i2c_address < 0 || i2c_address > 0x7F) {
                    print_error("I2C address out of range");
                    exit(1);
                }

                fprintf(stdout, "Setting I2C address to 0x%02X\n", i2c_address);
            }
        }

        // ...and issue passed in commands/data
        exit(matrix_commands(argc - 2, argv + 2));
    }
}


int matrix_commands(int argc, char *argv[]) {
    for (int i = 0 ; i < argc ; ++i) {
        char *token = argv[i];

        if (token[0] == '-') {
            switch (token[1]) {
                case 'a':   // ACTIVATE (DEFAULT) OR DEACTIVATE DISPLAY
                    {   
                        // Check for and get the optional argument
                        bool is_on = true;
                        if (i < argc - 1) {
                            token = argv[++i];
                            if (token[0] != '-') {
                                if (strlen(token) == 1) {
                                    is_on = (strcmp(token, "0") != 0);
                                } else {
                                    is_on = (strcmp(token, "off") != 0);
                                }
                            } else {
                                i -= 1;
                            }
                        }

                        // Apply the command
                        if (is_on) {
                            HT16K33_write_cmd(HT16K33_CMD_POWER_ON);
                            HT16K33_write_cmd(HT16K33_CMD_DISPLAY_ON);
                        } else {
                            HT16K33_write_cmd(HT16K33_CMD_DISPLAY_OFF);
                            HT16K33_write_cmd(HT16K33_CMD_POWER_OFF);    
                        }
                    }
                    break;

                case 'b':   // SET BRIGHTNESS
                    {
                        // Get the required argument
                        if (i < argc - 1) {
                            token = argv[++i];
                            if (token[0] != '-') {
                                int brightness = strtol(token, NULL, 0);

                                if (brightness < 0 || brightness > 15) {
                                    print_error("Brightness value out of range (0-15)");
                                    return 1;
                                }

                                // Apply the command
                                HT16K33_set_brightness(brightness);
                                break;
                            }
                        }
                        
                        print_error("No brightness value supplied");
                        return 1;
                    }
                
                case 'c':   // DISPLAY CHARACTER
                    {
                        // Get the required argument
                        if (i < argc - 1) {
                            token = argv[++i];
                            if (token[0] != '-') {
                                int ascii = strtol(token, NULL, 0);

                                if (ascii < 32 || ascii > 127) {
                                    print_error("Ascii value out of range (32-127)");
                                    return 1;
                                }

                                // Get an optional argument
                                bool do_centre = false;
                                if (i < argc - 1) {
                                    token = argv[++i];
                                    if (token[0] != '-') {
                                        if (strlen(token) == 1) {
                                            do_centre = (strcmp(token, "1") == 0);
                                        } else {
                                            do_centre = (strcmp(token, "true") == 0);
                                        }
                                    } else {
                                        i -= 1;
                                    }
                                }

                                // Perform the action
                                HT16K33_set_char(ascii, do_centre);
                                HT16K33_draw(); 
                                break;
                            }
                        }

                        print_error("No Ascii value supplied");
                        return 1;               
                    }

                case 'p':   // PLOT A POINT
                    {
                        // Get two required arguments
                        int x = -1, y = -1;
                        if (i < argc - 1) {
                            token = argv[++i];
                            if (token[0] != '-') {
                                x = strtol(token, NULL, 0);
                                if (i < argc - 1) {
                                    token = argv[++i];
                                    if (token[0] != '-') {
                                        y = strtol(token, NULL, 0);

                                        if (x < 0 || x > 7 || y < 0 || y > 7) {
                                            print_error("Co-ordinate out of range (0-7)");
                                            return 1;
                                        }

                                        // Get an optional argument
                                        int ink = 1;
                                        if (i < argc - 1) {
                                            token = argv[++i];
                                            if (token[0] != '-') {
                                                ink = strtol(token, NULL, 0);
                                                if (ink != 1 && ink != 0) ink = 1;
                                            }
                                        }

                                        // Perform the action
                                        HT16K33_plot((uint8_t)x, (uint8_t)y, ink == 1);
                                        HT16K33_draw(); 
                                        break;
                                    }
                                }
                            }
                        }

                        print_error("No co-ordinate value(s) supplied");
                        return 1; 
                    }
                    break;

                case 't':     // TEXT STRING
                    {
                        // Get one required argument
                        if (i < argc - 1) {
                            char *scroll_string = argv[++i];

                            // Get an optional argument
                            int scroll_delay = 250;
                            if (i < argc - 1) {
                                token = argv[++i];
                                if (token[0] != '-') {
                                    scroll_delay = strtol(token, NULL, 0);
                                }
                            }
                            
                            // Perform the action
                            HT16K33_print(scroll_string, (uint32_t)scroll_delay);
                            break;
                        }

                        print_error("No string supplied");
                        return 1; 
                    }


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
