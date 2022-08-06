#include <Wire.h>
#ifndef REFLECTANCE_SENSOR_H
#define REFLECTANCE_SENSOR_H
class ReflectanceSensor
{
private:
    int pinNumber;
    static bool leftOfTape;
public:
    ReflectanceSensor(int pinNum);
    int readSensor();
    static int findTapeSenseError(ReflectanceSensor left, ReflectanceSensor right, int error_2);
    static int findEdgeSenseError(ReflectanceSensor left, ReflectanceSensor right1, ReflectanceSensor right2, int error_2);
};
#endif
