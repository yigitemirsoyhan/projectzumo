#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>


#define LED_PIN 13
#define MZ80_PIN 6
#define NUM_SENSORS 6

//Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
ZumoBuzzer buzzer;



// Define an array for holding sensor values.
unsigned int sensorValues[NUM_SENSORS];
unsigned int positionVal = 0;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // --------------------------- Start Of The Calibration -------------------------
  reflectanceSensors.init();
  unsigned long startTime = millis();
  while (millis() - startTime < 5000)  //  the calibration take 5 seconds
  {
    reflectanceSensors.calibrate();
  }
  // ------------------- End Of The Calibration -----------------------
}

// Sensor Config

unsigned int mostLeftSensor() {
  if (sensorValues[0] < 600)
    return 1;
  else
    return 0;
}

unsigned int leftSensor() {
  if (sensorValues[1] < 600)
    return 1;
  else
    return 0;
}

unsigned int midLeftSensor() {
  if (sensorValues[2] < 600)
    return 1;
  else
    return 0;
}

unsigned int midRightSensor() {
  if (sensorValues[3] < 600)
    return 1;
  else
    return 0;
}

unsigned int count = 0 ;
unsigned int state = 0 ;

unsigned int rightSensor() {
  if (sensorValues[4] < 600)
    return 1;
  else
    return 0;
}

unsigned int mostRightSensor() {
  if (sensorValues[5] < 600)
    return 1;
  else
    return 0;
}
//sensor config end
void turnRight() {
  motors.setSpeeds(100, -100);
}

void turnLeft(){
  motors.setSpeeds(-200, 200);
}

void go() {
  motors.setSpeeds(600, 600);
}

void loop() {

  buzzer.playFrequency(1000, 500, 15);
  delay(3000);                            // After the buzzer we have 3 seconds to put the robot on ground
  unsigned long startTime = millis();
                                          // Stated the duration of the loop: 13.4 seconds 
  while (millis() - startTime < 13400){
      positionVal = reflectanceSensors.readLine(sensorValues);
      if (mostLeftSensor() == 1) {
        motors.setSpeeds(-200,-200);
        delay(200);
        motors.setSpeeds(-400, 400);
        delay(300);
      } else {
        turnRight();   //Border Detect 
      }
      if(state == 0){
          if (!digitalRead(MZ80_PIN)) {
            state = 1 ;
           
            
          } 
      }else{
        if (!digitalRead(MZ80_PIN)) {
            state = 1 ;
           
            
          }else{
            state = 0;
            count++;
          } 

      }
    }
  motors.setSpeeds(0,0);  // Robot stops after loop
  count = ceil((count/2));  
  digitalWrite(LED_PIN, LOW);
  delay(2000);           // this delay give us enough time to get closer to robot to see LED.
  while(count>0){
    motors.setSpeeds(0,0);
    delay(1000);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW); // LED Blinking loop for counting purpose
    delay(500);
    count--;
  }
  while(1){
    motors.setSpeeds(0,0);  // stops forever
  }  
}
