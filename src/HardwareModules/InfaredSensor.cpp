#include <Wire.h>
#include"../src/HardwareModules/InfaredSensor.h"
#include "../src/HardwareModules/HardwareDefinitions.h"

InfaredSensor :: InfaredSensor(int readPin, int resetPin, int rightSwitch, int leftSwitch){
    this -> readPin = readPin;
    this -> resetPin = resetPin;
    this -> leftSwitchPin = leftSwitch;
    this -> rightSwitchPin = rightSwitch;
    pinMode(this -> resetPin, OUTPUT);
    pinMode(this -> readPin, INPUT);
    pinMode(leftSwitchPin, OUTPUT);
    pinMode(rightSwitchPin, OUTPUT);
    digitalWrite(leftSwitchPin, LOW);
    digitalWrite(rightSwitchPin, LOW);
}

InfaredSensor InfaredSensor :: instance = InfaredSensor(INFARED_SENSOR_READ_PIN_NUM, INFARED_RESET_PIN, INFARED_SENSOR_RIGHT_SWITCH_PIN, INFARED_SENSOR_LEFT_SWITCH_PIN);

InfaredSensor InfaredSensor :: GetInfaredSensor(){
    return instance;
}

bool InfaredSensor :: leftOfBeacon;

int InfaredSensor :: GetIRError(int secondError){
    int infaredVal[] ={0,0};
    int errorVal;
    digitalWrite(leftSwitchPin, HIGH);
    digitalWrite(resetPin, HIGH);
    digitalWrite(resetPin, LOW);
    delay(1000);
    if(analogRead(readPin)> IR_THRESHOLD){
        infaredVal[0] = 1;
    } else{
        infaredVal[0] = 0;
    }
    digitalWrite(leftSwitchPin, LOW);
    digitalWrite(rightSwitchPin, HIGH);
    digitalWrite(resetPin, HIGH);
    digitalWrite(resetPin, LOW);
    delay(1000);
    if(analogRead(readPin)> IR_THRESHOLD){
        infaredVal[1] = 1;
    } else{
        infaredVal[1] = 0;
    }
    digitalWrite(rightSwitchPin, LOW);   
  if(infaredVal[0] == 1){
    leftOfBeacon = false;
    switch(infaredVal[1]){
    case 0:
    errorVal = 1;
    break;
    case 1:
    errorVal = 0;
    break;
    }
  }
  if(infaredVal[1] == 1){
    leftOfBeacon = true;
    switch(infaredVal[0]){
    case 0:
      errorVal = -1;
      break;
    case 1:
      errorVal = 0;
      break;
    }
  }
  if(infaredVal[0] == 0 && infaredVal[1]==0){
    switch (leftOfBeacon) 
    {
    case true:
      errorVal = -secondError;
      break;
  
    case false:
      errorVal = secondError;
      break;
    }
  }
  return errorVal;
}



