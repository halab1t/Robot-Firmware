#include <Wire.h>
#include "ReflectanceSensor.h"

ReflectanceSensor::ReflectanceSensor(int pinNum){
this -> pinNumber = pinNum;
pinMode(pinNumber, INPUT);
}
int ReflectanceSensor::readSensor(){
return (digitalRead(pinNumber));
}
bool ReflectanceSensor :: leftOfTape;
int ReflectanceSensor :: findTapeSenseError(ReflectanceSensor left, ReflectanceSensor right, int error_2){
  int reflectanceVal[] = {left.readSensor(),right.readSensor()};
  int errorVal;
  if(reflectanceVal[0] == 1){
    leftOfTape = false;
    switch(reflectanceVal[1]){
    case 0:
    errorVal = 1;
    break;
    case 1:
    errorVal = 0;
    break;
    }
  }
  if(reflectanceVal[1] == 1){
    leftOfTape = true;
    switch(reflectanceVal[0]){
    case 0:
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
      errorVal = -error_2;
      break;
  
    case false:
      errorVal = error_2;
      break;
    }
  }
  return errorVal;
}
int ReflectanceSensor :: findEdgeSenseError(ReflectanceSensor left, ReflectanceSensor right1, ReflectanceSensor right2, int error_2){// where right2 is mounted further out than right1
  int reflectanceVal[] = {left.readSensor(), right1.readSensor(), right2.readSensor()};
  int error;
  if(reflectanceVal[0] == 1 && reflectanceVal[1] == 1){
    // throw OverTheEdgeException();
  }
  if(reflectanceVal[0] == 1 && reflectanceVal[1] == 0){
    switch (reflectanceVal[2])
    {
      case 1 : 
        // throw OverTheEdgeException();
        break;
    
      case 0 :
        error = -10;
        break;
    }
  }
  if(reflectanceVal[0] == 0 && reflectanceVal[1] == 0){
    switch (reflectanceVal[2])
    {
      case 1:
        error = 0;
        break;
    
      case 0:
        error = -1;
        break;
    }
  }
  if(reflectanceVal[0]==0 && reflectanceVal[1] == 1){
    error = 1;
  }
return error;
}
