#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "../src/HardwareModules/DriveBaseHandler.h"
#include "../src/HardwareModules/InfaredSensor.h"
#include "../src/HardwareModules/HardwareDefinitions.h"
#include "../src/HardwareModules/TapeSensor.h"



int leftIR = 0, rightIR = 0;
Adafruit_SSD1306 display_handler (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int previousState_counter = 0, currentState_counter = 0;
int currentError_val =0, previousError_val = 0, tempErrorVal = 0;
int currentTime_us = 0, previousTime_us = 0;
int derivative = 0, PID_term = 0;
int k_d = 72, k_p = 80, terror = 10;

int reflectanceVal[] = {0,0};
int currentMeasurement_no = 0;
bool leftOf_tape;

#ifdef DRIVE_BASE
int dutyCycle_left = STARTING_DUTY_CYCLE, dutyCycle_right = STARTING_DUTY_CYCLE;
Motor leftWheel(LEFT_MOTOR_FORWARDS_PIN_NUM, LEFT_MOTOR_REVERSE_PIN_NUM, LEFT_MOTOR_FORWARDS_PIN_NAME, LEFT_MOTOR_REVERSE_PIN_NAME);
Motor rightWheel(RIGHT_MOTOR_FORWARDS_PIN_NUM, RIGHT_MOTOR_REVERSE_PIN_NUM, RIGHT_MOTOR_FORWARDS_PIN_NAME, RIGHT_MOTOR_REVERSE_PIN_NAME);
TapeSensor TapeSensor = TapeSensor::GetTapeSensor();
#endif
#ifdef IR
  InfaredSensor IRSensors = InfaredSensor::GetInfaredSensor();
#endif
#ifdef TUNING_MODE
void pid_control_loop(){
  int p_temp = analogRead(K_P_PIN)/10;
  int error_temp = analogRead(ERROR_2)/100;
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
  display_handler.print(terror);
}

void button_press(){
  k_p = analogRead(K_P_PIN)/10;
  terror = analogRead(ERROR_2)/100;
  k_d = analogRead(K_D_PIN)/10;
}
#endif
void setup() {
    display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    #ifdef TUNING_MODE
    attachInterrupt(digitalPinToInterrupt(BUTTON_SWITCH),button_press,RISING);
    pinMode(K_D_PIN, INPUT);
    pinMode(K_P_PIN, INPUT);
    pinMode(ERROR_2, INPUT);
    pinMode(INFARED_RESET_PIN, OUTPUT);
    pinMode(INFARED_SENSOR_LEFT_SWITCH_PIN, OUTPUT);
    pinMode(INFARED_SENSOR_RIGHT_SWITCH_PIN, OUTPUT);
    pinMode(INFARED_SENSOR_READ_PIN_NUM, INPUT);
    
    display_handler.clearDisplay();
    display_handler.setTextSize(1);
    display_handler.setTextColor(SSD1306_WHITE);
    display_handler.setCursor(0,0);
    display_handler.print("Running both motors!");
    display_handler.display();
  #endif
  #ifdef DRIVE_BASE
  leftWheel.motorSetup(dutyCycle_left, MOTOR_FREQ);
  rightWheel.motorSetup(dutyCycle_right, MOTOR_FREQ);
  #endif

  delay(2000);
}

void loop() {
    // reflectanceVal[0] = leftReflectance.readSensor();
    // reflectanceVal[1] = rightReflectance.readSensor();
    // display_handler.clearDisplay();
    // display_handler.setCursor(0,0);
    // display_handler.print("left Ref :");
    // display_handler.println(reflectanceVal[0]);
    // display_handler.print("right Ref :");
    // display_handler.println(reflectanceVal[1]);
    // display_handler.print("PID term : ");
    // display_handler.println(PID_term);
    // display_handler.print("Derivative : ");
    // display_handler.println(derivative);
    // display_handler.print("error :");
    // display_handler.println(currentError_val);
    // pid_control_loop();
    // display_handler.display();
    // tempErrorVal = TapeSensor.getTSError(terror);
    digitalWrite(INFARED_SENSOR_LEFT_SWITCH_PIN, HIGH);
    digitalWrite(INFARED_RESET_PIN, HIGH);
    delay(2);
    digitalWrite(INFARED_RESET_PIN, LOW);
    delay(2);
    leftIR = analogRead(INFARED_SENSOR_READ_PIN_NUM);
    delay(1);
    digitalWrite(INFARED_SENSOR_LEFT_SWITCH_PIN, LOW);
    digitalWrite(INFARED_SENSOR_RIGHT_SWITCH_PIN, HIGH);
    digitalWrite(INFARED_RESET_PIN, HIGH);
    delay(2);
    digitalWrite(INFARED_RESET_PIN, LOW);
    delay(2);
    rightIR = analogRead(INFARED_SENSOR_READ_PIN_NUM);
    delay(1);
    digitalWrite(INFARED_SENSOR_RIGHT_SWITCH_PIN, LOW);
    display_handler.clearDisplay();
    display_handler.setCursor(0,0);
    display_handler.print("Left Sensor:");
    display_handler.println(leftIR);
    display_handler.print("Right Sensor:");
    display_handler.println(rightIR);
    display_handler.display();

    // tempErrorVal = IRSensors.getIRError();
    // if(!(currentError_val == tempErrorVal)){
    //   previousTime_us = currentTime_us;
    //   previousError_val = currentError_val;
    //   currentError_val = tempErrorVal;
    // }
    // currentTime_us = micros();
    // derivative = COVERSION_TO_ds*(float)(currentError_val - previousError_val)/(float)(currentTime_us - previousTime_us);
    // PID_term = k_p*(currentError_val) - k_d*(derivative);
    // leftWheel.runMotor(dutyCycle_left - PID_term, motorBias::forwards, MOTOR_FREQ);
    // rightWheel.runMotor(dutyCycle_right + PID_term, motorBias::forwards, MOTOR_FREQ);





}


