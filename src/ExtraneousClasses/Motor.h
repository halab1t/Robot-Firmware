#ifndef MOTOR_H
#define MOTOR_H
#include <Wire.h>
enum motorBias{
    forwards,
    reverse
};
class Motor
{
private:
 int forwardPin;
 int reversePin;
 PinName forwardPin_name;
 PinName reversePin_name;

public:
    Motor(int forwards, int backwards, PinName forewardsName, PinName backwardsName);
    void motorSetup(int dutyCycle, int motorFreq);
    void runMotor(int dutyCycle, motorBias bias, int motorFreq);
};

#endif

