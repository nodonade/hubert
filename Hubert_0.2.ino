#include <Servo.h>
#include <Wiichuck.h>
#include <Wire.h>

#define lAnklePin 2
#define lHipPin 3
#define lElbowPin 4
#define lShoulderPin 5
#define headPin 6
#define rShoulderPin 7
#define rElbowPin 8
#define rHipPin 9
#define rAnklePin 10

Wiichuck chuck;


Servo lAnkle; // create servo object to control a servo
Servo lHip;
Servo lElbow;
Servo lShoulder;
Servo head;
Servo rShoulder;
Servo rElbow;
Servo rHip;
Servo rAnkle;


            // variable to store the servo position
int lAnklePos = 100; // create servo object to control a servo
int lHipPos = 100;
int lElbowPos = 160;
int lShoulderPos = 180;
int headPos = 90;
int rShoulderPos = 0;
int rElbowPos = 10;
int rHipPos = 100;
int rAnklePos = 100;
int val;

void setup(){
  chuck.init(0,0);
  chuck.calibrate();

  Serial.begin(9600);

  lAnkle.attach(lAnklePin);
  lHip.attach(lHipPin);
  lElbow.attach(lElbowPin);
  lShoulder.attach(lShoulderPin);
  head.attach(headPin);
  rShoulder.attach(rShoulderPin);
  rElbow.attach(rElbowPin);
  rHip.attach(rHipPin);
  rAnkle.attach(rAnklePin);

  rHip.write(rHipPos);
  rAnkle.write(rAnklePos);
  lAnkle.write(lAnklePos);
  lHip.write(lHipPos);

  head.write(headPos);

  lElbow.write(lElbowPos);
  lShoulder.write(lShoulderPos);
  rElbow.write(rElbowPos);
  rShoulder.write(rShoulderPos);
}

void loop(){
  if(chuck.poll()){
    /*
    Serial.print("x: ");
    Serial.print(chuck.accelX());
    Serial.print(" y: ");
    Serial.print(chuck.accelY());
    Serial.print(" z: ");
    Serial.println(chuck.accelZ());
    */
    
    Serial.print("x: ");
    Serial.print(chuck.joyX());
    Serial.print(" y: ");
    Serial.println(chuck.joyY());

    Serial.print("C: ");
    Serial.print(chuck.buttonC());
    Serial.print(" Z: ");
    Serial.println(chuck.buttonZ());

    //Wave Hello
    if (chuck.buttonC()) {
      rShoulder.write(180);
      lShoulder.write(0);
      lElbow.write(90);
      for (rElbowPos = 20; rElbowPos <= 180; rElbowPos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        rElbow.write(rElbowPos);              // tell servo to go to position in variable 'pos'
        delay(5);                       // waits 15ms for the servo to reach the position
      }
      for (rElbowPos = 180; rElbowPos >= 20; rElbowPos -= 1) { // goes from 180 degrees to 0 degrees
        rElbow.write(rElbowPos);              // tell servo to go to position in variable 'pos'
        delay(5);                       // waits 15ms for the servo to reach the position
      }
    }
    else {
      rShoulder.write(0);
      lShoulder.write(180);
      lElbow.write(160);
      rElbow.write(10);
    }

    // Head control
    headPos = chuck.joyX();            // reads the value of the potentiometer (value between 0 and 1023)
    headPos = map(headPos, 255, 0, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    head.write(headPos);                  // sets the servo position according to the scaled value

    // Ankle control
    
    rAnklePos = chuck.joyY();            // reads the value of the potentiometer (value between 0 and 1023)
    rAnklePos = map(rAnklePos, 0, 255, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    rAnkle.write(rAnklePos);
    
    
    lAnklePos = chuck.joyY();            // reads the value of the potentiometer (value between 0 and 1023)
    lAnklePos = map(lAnklePos, 0, 255, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    lAnkle.write(lAnklePos);

    lHipPos = chuck.joyY();            // reads the value of the potentiometer (value between 0 and 1023)
    lHipPos = map(lHipPos, 0, 255, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    lHip.write(lHipPos);

    rHipPos = chuck.joyY();            // reads the value of the potentiometer (value between 0 and 1023)
    rHipPos = map(rHipPos, 0, 255, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    rHip.write(rHipPos);
    
  }
  delay(100);
}
