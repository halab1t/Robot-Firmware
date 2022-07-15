#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Arduino.h"
#include <Motor.h>
#include <Oled.h>
#include <ReflectanceSensor.h>

#define LED_BUILTIN PB2
#define MOTOR_FREQ 50
#define STARTING_DUTY_CYCLE 1000                                                                                                                                                                          
#define SCREEN_HEIGHT 64 // oled height in pixels
#define SCREEN_WIDTH  128 // oled width in pixels
#define OLED_RESET -1
#define COVERSION_TO_ds 100000
#define K_D_PIN PA6
#define K_P_PIN PA7
#define ERROR_2 PA5
#define BUTTON_SWITCH PB5

Adafruit_SSD1306 display_handler (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int previousState_counter = 0, currentState_counter = 0;
int currentError_val =0, previousError_val = 0;
int currentTime_ms = 0, previousTime_ms = 0;
int derivative = 0, PID_term = 0;
int k_d = 1, k_p = 10, error_2 = 3;
int dutyCycle_left = STARTING_DUTY_CYCLE, dutyCycle_right = .7*STARTING_DUTY_CYCLE;
int reflectanceVal[] = {0,0};
bool leftOf_tape;
Motor leftWheel(PA3, PA2, PA_3, PA_2);
Motor rightWheel(PA0, PA1, PA_0, PA_1);
ReflectanceSensor leftReflectance(PB3);
ReflectanceSensor rightReflectance(PB4);

void pid_control_loop(){
  int p_temp = analogRead(K_P_PIN)/10;
  int error_temp = analogRead(ERROR_2);
  int d_temp = analogRead(K_D_PIN)/10;


  display_handler.print("P: ");
  display_handler.print(p_temp);
  display_handler.print("   ");
  display_handler.println(k_p);
  display_handler.print("D: ");
  display_handler.print(d_temp);
  display_handler.print("   ");
  display_handler.println(k_d);
  display_handler.print("E: ");
  display_handler.print(error_temp);
  display_handler.print("   ");
  display_handler.print(error_2);
}

void button_press(){
  k_p = analogRead(K_P_PIN)/10;
  error_2 = analogRead(ERROR_2)/100;
  k_d = analogRead(K_D_PIN)/10;
}
// ReflectanceSensor leftEdge()

// void handle_interrupt_Schmidt();

void setup() {
  attachInterrupt(digitalPinToInterrupt(BUTTON_SWITCH),button_press,RISING);
pinMode(K_D_PIN, INPUT);
pinMode(K_P_PIN, INPUT);
pinMode(ERROR_2, INPUT);
  
    display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display_handler.clearDisplay();
    display_handler.setTextSize(1);
    display_handler.setTextColor(SSD1306_WHITE);
    display_handler.setCursor(0,0);
    display_handler.print("Running both motors!");
    display_handler.display();
 leftWheel.motorSetup(dutyCycle_left, MOTOR_FREQ);
 rightWheel.motorSetup(dutyCycle_right, MOTOR_FREQ);


  delay(2000);
}

void loop() {
  

previousError_val = currentError_val;
reflectanceVal[0] = leftReflectance.readSensor();
reflectanceVal[1] = rightReflectance.readSensor();
 display_handler.clearDisplay();
 pid_control_loop();
 display_handler.setCursor(0,0);
    display_handler.print("left Ref :");
    display_handler.println(reflectanceVal[0]);
    display_handler.print("right Ref :");
    display_handler.println(reflectanceVal[1]);
    display_handler.print("PID term : ");
    display_handler.println(PID_term);
      display_handler.print("Derivative : ");
    display_handler.println(derivative);
    display_handler.display();
if(reflectanceVal[0] == 1){
  leftOf_tape = false;
  switch(reflectanceVal[1]){
    case 0:
    currentError_val = 1;
    break;
    case 1:
    currentError_val = 0;
    break;
  }
}
if(reflectanceVal[1] == 1){
  leftOf_tape = true;
  switch(reflectanceVal[0]){
    case 0:
    currentError_val = -1;
    break;
    case 1:
    currentError_val = 0;
    break;
  }
}
if(reflectanceVal[0] == 0 && reflectanceVal[1]==0){
  switch (leftOf_tape)
  {
  case true:
    currentError_val = -error_2;
    break;
  
  case false:
    currentError_val = error_2;
    break;
  }
}

if(!(currentError_val == previousError_val)){
  previousTime_ms = currentTime_ms;
}
currentTime_ms = micros();
derivative = COVERSION_TO_ds*(float)(currentError_val - previousError_val)/(float)(currentTime_ms - previousTime_ms);
PID_term = k_p*(currentError_val) - k_d*(derivative);
leftWheel.runMotor(dutyCycle_left - PID_term, forwards, MOTOR_FREQ);
rightWheel.runMotor(dutyCycle_right + PID_term, forwards, MOTOR_FREQ);


}


