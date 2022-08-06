#include "../src/HardwareModules/TapeSensor.h"
#include"../src/HardwareModules/HardwareDefinitions.h"
#include <Wire.h>

TapeSensor :: TapeSensor(int leftPin, int rightPin){
    this ->leftPin = leftPin;
    this ->rightPin = rightPin;
    pinMode(leftPin, INPUT);
    pinMode(rightPin, INPUT);
}

bool TapeSensor:: leftOfTape;

TapeSensor TapeSensor:: instance = TapeSensor(LEFT_REFLECTANCE_PIN_NUM, RIGHT_REFLECTANCE_PIN_NUM);

TapeSensor TapeSensor:: GetTapeSensor(){
    return instance;
}

int TapeSensor:: GetTSError(int secondaryErrorVal){
    int reflectanceVal[] = {digitalRead(leftPin),digitalRead(rightPin)};
    int errorVal;
  if(reflectanceVal[0] == 1){
    switch(reflectanceVal[1]){
    case 0:
    leftOfTape = false;
    errorVal = 1;
    break;
    case 1:
    errorVal = 0;
    break;
    }
  }
  if(reflectanceVal[1] == 1){
    switch(reflectanceVal[0]){
    case 0:
      leftOfTape = true;
      errorVal = -1;
      break;
    case 1:
      errorVal = 0;
      break;
    }
  }
  if(reflectanceVal[0] == 0 && reflectanceVal[1]==0){
    switch (leftOfTape) 
    {
    case true:
      errorVal = -secondaryErrorVal;
      break;
  
    case false:
      errorVal = secondaryErrorVal;
      break;
    }
  }
  return errorVal;
}

bool TapeSensor:: OnTape(){
  int reflectanceVal[] = {digitalRead(leftPin),digitalRead(rightPin)};
  if(reflectanceVal[0] == 1 && reflectanceVal[1]==1){
    return true;
  }else{
    return false;
  }
}