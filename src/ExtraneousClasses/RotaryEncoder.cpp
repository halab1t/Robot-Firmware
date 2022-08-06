#include "RotaryEncoder.h"
void RotaryEncoder :: EncoderTick() {//confirm that this is right
    if(analogRead(phasePinNum)== HIGH){
        numTicks ++;
    }else{
        numTicks --;
    }
    distance_in = (numTicks)*CIRC_OF_WHEELS_INCHES/ENCODER_TICKS_PER_SPIN;
    sampleNum++;
    if(sampleNum == SAMPLE_SIZE){
        currentTime_ms = millis();
        speed_in_per_ms = DIST_PER_SAMPLE_SIZE/(currentTime_ms - previousTime_ms);
        previousTime_ms = currentTime_ms;
        sampleNum = 0; 
    }
}
RotaryEncoder :: RotaryEncoder(int phasePin, int distPin){
    this -> phasePinNum = phasePin;
    this -> distPinNum = distPin;
    this -> distance_in = 0;
    this -> numTicks = 0;
    this -> previousTime_ms = millis();
    this -> sampleNum = 0;
    pinMode(phasePinNum, INPUT);
    pinMode(distPinNum, INPUT);
    attachInterrupt(digitalPinToInterrupt(distPinNum), std::bind(&RotaryEncoder :: EncoderTick, this), RISING);
}

void RotaryEncoder :: Reset(){
    distance_in = 0;
    numTicks = 0;
}

int RotaryEncoder :: GetSpeed(){
    return speed_in_per_ms;
}

int RotaryEncoder :: GetDistance(){
    return distance_in;
}
    


