#include "PID.h"
#include "../src/HardwareModules/HardwareDefinitions.h"

PID :: PID(int kp, int kd){
    this -> kP = kp;
    this -> kD = kd;
    this -> currentTime_us = 0;
    this -> previousTime_us = 0;
    this -> currentError = 0;
    this -> previousError = 0;
}

int PID:: GetPID(int error){
    int derivative, PID_term;
    if(!(currentError == error)){
      previousTime_us = currentTime_us;
      previousError = currentError;
      currentError = error;
    }
    currentTime_us = micros();
    derivative = COVERSION_TO_ds*(float)(currentError - previousError)/(float)(currentTime_us - previousTime_us);
    PID_term = kP*(currentError) - kD*(derivative);
    return PID_term;
}
