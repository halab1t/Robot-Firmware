#include "Motor.h"
#include <Wire.h>
Motor::Motor(int forwards, int backwards, PinName forewardsName, PinName backwardsName){
    this ->forwardPin = forwards;
    this ->reversePin = backwards;
    this ->forwardPin_name = forewardsName;
    this ->reversePin_name = backwardsName;
}
void Motor:: motorSetup(int dutyCycle, int motorFreq){
    pinMode(forwardPin, OUTPUT);
    pinMode(reversePin, OUTPUT);
    pwm_start(forwardPin_name, motorFreq, dutyCycle, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(reversePin_name, motorFreq, 0, RESOLUTION_12B_COMPARE_FORMAT);
} 
void Motor:: runMotor(int dutyCycle, motorBias bias, int motorFreq){
    if (bias == forwards){
        pwm_start(reversePin_name, motorFreq, 0, RESOLUTION_12B_COMPARE_FORMAT);
        pwm_start(forwardPin_name, motorFreq, dutyCycle, RESOLUTION_12B_COMPARE_FORMAT);
    } else if(bias == reverse){
        pwm_start(forwardPin_name, motorFreq, 0, RESOLUTION_12B_COMPARE_FORMAT);
        pwm_start(reversePin_name, motorFreq, dutyCycle, RESOLUTION_12B_COMPARE_FORMAT);
    }
}

