#ifndef INFARED_SENSOR_H
#define INFARED_SENSOR_H
#include "../src/HardwareModules/HardwareDefinitions.h"
#include <Wire.h>
class InfaredSensor
{
private:
    InfaredSensor(int readPin, int resetPin, int rightSwitch, int leftSwitch);
    static InfaredSensor instance;
    int readPin;
    int leftSwitchPin;
    int rightSwitchPin;
    int resetPin;
    static bool leftOfBeacon;
    
public:
    static InfaredSensor GetInfaredSensor();
    int GetIRError(int secondError);
};
#endif

