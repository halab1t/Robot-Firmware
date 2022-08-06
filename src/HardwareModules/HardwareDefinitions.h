#ifndef HARDWARE_DEFINITIONS_H
#define HARDWARE_DEFINITIONS_H
#define TUNING_MODE
#define REFLECTANCE_AND_EDGE
#define ZIP_LINE
#define DRIVE_BASE
#define IR
#define CLAW
#define LED_BUILTIN PB2
#define SCREEN_HEIGHT 64 // oled height in pixels
#define SCREEN_WIDTH  128 // oled width in pixels
#define OLED_RESET -1
#define MOTOR_FREQ 50
#define STARTING_DUTY_CYCLE 1000                                                                                                                                                                          
#define COVERSION_TO_ds 100000
#ifdef TUNING_MODE
    #define K_D_PIN PA6
    #define K_P_PIN PA7
    #define ERROR_2 PA5
    #define BUTTON_SWITCH PB5
#endif
#ifdef REFLECTANCE_AND_EDGE
    #define LEFT_REFLECTANCE_PIN_NUM PB15
    #define RIGHT_REFLECTANCE_PIN_NUM PA8
    #define RIGHT_EDGE_REFLECTANCE_FURTHEST PA9
    #define RIGHT_EDGE_REFLECTANCE_INNER PA10
    #define LEFT_EDGE_REFLECTANCE PA11
    #define KP_TAPE
    #define KD_TAPE
    #define KP_EDGE
    #define KD_EDGE
#endif
#ifdef ZIP_LINE
    #define LEAD_SCREW_MOTOR_FORWARDS PA3
    #define LEAD_SCREW_MOTOR_FORWARDS_NAME PA_3
    #define LEAD_SCREW_MOTOR_REVERSE PA2
    #define LEAD_SCREW_MOTOR_REVERSE_NAME PA_2
    #define ZIP_LINE_MOTOR_FORWARDS PA1
    #define ZIP_LINE_MOTOR_FORWARDS_NAME PA_1
    #define ZIP_LINE_MOTOR_REVERSE PA0
    #define ZIP_LINE_MOTOR_REVERSE_NAME PA_0
    #define FULLY_EXTENDED_LIMIT_SWITCH B14
    #define FULLY_COMPRESSED_LIMIT_SWITCH B13
    #define ZIPLINE_DETECTING_LIMIT_SWITCH B12
#endif
#ifdef DRIVE_BASE
    #define RIGHT_MOTOR_FORWARDS_PIN_NUM PB6
    #define RIGHT_MOTOR_FORWARDS_PIN_NAME PB_6
    #define RIGHT_MOTOR_REVERSE_PIN_NUM PB7
    #define RIGHT_MOTOR_REVERSE_PIN_NAME PB_7
    #define LEFT_MOTOR_FORWARDS_PIN_NUM PB8
    #define LEFT_MOTOR_FORWARDS_PIN_NAME PB_8
    #define LEFT_MOTOR_REVERSE_PIN_NUM PB9
    #define LEFT_MOTOR_REVERSE_PIN_NAME PB_9
    #define LEFT_MOTOR_ENCODER PB0
    #define LEFT_MOTOR_ENCODER_PHASE PA7
    #define RIGHT_MOTOR_ENCODER PA6
    #define RIGHT_MOTOR_ENCODER_PHASE PA5 
    #define KP_ENCODER
    #define KD_ENCODER
    #define ENCODER_TICKS_PER_SPIN 144 //1441 normally but we mod 10
    #define CIRC_OF_WHEELS_INCHES 7.85
    #define DIST_PER_SAMPLE_SIZE 78.5/144
    #define SAMPLE_SIZE 10
#endif
    #ifdef IR
    #define IR_THRESHOLD 200
    #define INFARED_SENSOR_LEFT_SWITCH_PIN PA12
    #define INFARED_SENSOR_RIGHT_SWITCH_PIN PA15
    #define INFARED_SENSOR_READ_PIN_NUM PB1
    #define INFARED_RESET_PIN PB10
    #define KP_IR
    #define KD_IR
#endif
#ifdef CLAW
    #define CLAW_BLUEPILL_COMM_OUT PB4
    #define CALW_BLUEPILL_COMM_IN PB5
#endif
#endif
