#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H
#include <Wire.h>
#include "../src/HardwareModules/HardwareDefinitions.h"
class RotaryEncoder
{
private:
    void EncoderTick();
    volatile int numTicks;
    volatile int distance_in;
    volatile int speed_in_per_ms;
    volatile int previousTime_ms;
    volatile int currentTime_ms;
    volatile int sampleNum;
    int phasePinNum;
    int distPinNum;
public:
    RotaryEncoder(int phasePin, int distPin);
    void Reset();
    int GetDistance();
    int GetSpeed();
};
#endif