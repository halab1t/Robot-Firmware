#ifndef DRIVE_BASE_HANDLER_H
#define DRIVE_BASE_HANDLER_H
#include "../src/ExtraneousClasses/Motor.h"
#include "../src/HardwareModules/HardwareDefinitions.h"
#include "../src/ExtraneousClasses/RotaryEncoder.h"
enum Direction{
    left,
    right
};
class DriveBaseHandler
{
private:
    Motor leftWheel;
    Motor rightWheel;
    RotaryEncoder rightWheelEncoder;
    RotaryEncoder leftWheelEncoder;
    static DriveBaseHandler instance;
    DriveBaseHandler(Motor left, Motor right, RotaryEncoder leftEncoder, RotaryEncoder rightEncoder);
public:
    static DriveBaseHandler getInstance();
    void Stop();
    void Turn(int angle_degrees, Direction direction);
    void Start();
    void GoStraight(int distance);
    bool FindTape();
};

#endif