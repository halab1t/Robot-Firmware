#ifndef TAPE_SENSOR_H
#define TAPE_SENSOR_H
#include "../src/HardwareModules/HardwareDefinitions.h"
class TapeSensor
{
private:
    TapeSensor(int leftPin, int rightPin);
    int leftPin;
    int rightPin;
    static TapeSensor instance;
    static bool leftOfTape;
public:
    static TapeSensor GetTapeSensor();
    int GetTSError(int secondaryErrorVal);
    bool OnTape();
};


#endif