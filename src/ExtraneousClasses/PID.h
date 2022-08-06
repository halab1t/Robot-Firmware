#ifndef PID_H
#define PID_H
#include <Wire.h>
class PID{
private:
    int kP;
    int kD;
    int previousTime_us;
    int currentTime_us;
    int previousError;
    int currentError;
public:
    PID(int kp, int kd);
    int GetPID(int error);
};
#endif