/*************************************************** 
  This code uses an Adafruit 16-channel PWM & Servo driver hat
  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  This performs some random servo movements to make an InMoov
  robot feel more alive. It only uses a subset of servos,
  adjust to your needs
****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "AdaHat.h"

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVO_HEAD_TWIST_MIN  180 // this is the 'minimum' pulse length count (out of 4096)
#define SERVO_HEAD_TWIST_MAX  580 // this is the 'maximum' pulse length count (out of 4096)

#define SERVO_HEAD_MOUTH_MIN 135
#define SERVO_HEAD_MOUTH_MAX 550

#define SERVO_RIGHT_BICEP_TWIST_MIN 180
#define SERVO_RIGHT_BICEP_TWIST_MAX 580

// most servos support PWMs from 150 to 600
#define SERVO_UNCALIBRATED_DEFAULT_MIN 150
#define SERVO_UNCALIBRATED_DEFAULT_MAX 600

// define which pins are for which servos

#define PIN_HEAD_TWIST 0
#define PIN_HEAD_MOUTH 1
#define PIN_RIGHT_BICEP_TWIST 2

#define PIN_RIGHT_THUMB 3
#define PIN_RIGHT_INDEX 4
#define PIN_RIGHT_MIDDLE 5
#define PIN_RIGHT_RING 6
#define PIN_RIGHT_PINKY 7

// min/max angles for each servo

#define HEAD_TWIST_MIN 40 //to the right
#define HEAD_TWIST_MAX 100 // to the left

#define HEAD_MOUTH_MIN 0
#define HEAD_MOUTH_MAX 40

#define RIGHT_BICEP_TWIST_MIN 45
#define RIGHT_BICEP_TWIST_MAX 120

#define RIGHT_THUMB_MIN 10
#define RIGHT_THUMB_MAX 100

#define RIGHT_INDEX_MIN 0
#define RIGHT_INDEX_MAX 80

#define RIGHT_MIDDLE_MIN 90 // some issues with this servo
#define RIGHT_MIDDLE_MAX 90

#define RIGHT_RING_MIN 20
#define RIGHT_RING_MAX 165

#define RIGHT_PINKY_MIN 45
#define RIGHT_PINKY_MAX 165


AdaHat hat(0);

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));

  hat.setup();
  hat.setupServo(PIN_HEAD_TWIST, SERVO_HEAD_TWIST_MIN, SERVO_HEAD_TWIST_MAX);
  hat.setupServo(PIN_HEAD_MOUTH, SERVO_HEAD_MOUTH_MIN, SERVO_HEAD_MOUTH_MAX);
  hat.setupServo(PIN_RIGHT_BICEP_TWIST, SERVO_RIGHT_BICEP_TWIST_MIN, SERVO_RIGHT_BICEP_TWIST_MAX);
  hat.setupServo(PIN_RIGHT_THUMB, SERVO_UNCALIBRATED_DEFAULT_MIN, SERVO_UNCALIBRATED_DEFAULT_MAX);
  hat.setupServo(PIN_RIGHT_INDEX, SERVO_UNCALIBRATED_DEFAULT_MIN, SERVO_UNCALIBRATED_DEFAULT_MAX);
  hat.setupServo(PIN_RIGHT_MIDDLE, SERVO_UNCALIBRATED_DEFAULT_MIN, SERVO_UNCALIBRATED_DEFAULT_MAX);
  hat.setupServo(PIN_RIGHT_RING, SERVO_UNCALIBRATED_DEFAULT_MIN, SERVO_UNCALIBRATED_DEFAULT_MAX);
  hat.setupServo(PIN_RIGHT_PINKY, SERVO_UNCALIBRATED_DEFAULT_MIN, SERVO_UNCALIBRATED_DEFAULT_MAX);
  

}

void loop() {

  //hat.setServoDegrees(servonum,90);
  hat.setServoDegrees(PIN_HEAD_TWIST, ( HEAD_TWIST_MIN + HEAD_TWIST_MAX ) / 2);
  hat.setServoDegrees(PIN_HEAD_MOUTH, HEAD_MOUTH_MIN);
  
  delay(2000);

  closeHand();

  delay(2000);


  hat.setServoDegrees(PIN_RIGHT_BICEP_TWIST, random(RIGHT_BICEP_TWIST_MIN, RIGHT_BICEP_TWIST_MAX));
  hat.setServoDegrees(PIN_RIGHT_THUMB, RIGHT_THUMB_MAX);

  delay(5000);

  hat.setServoDegrees(PIN_HEAD_TWIST, random(HEAD_TWIST_MIN, HEAD_TWIST_MAX));
  rollOpenAndCloseHand();

  delay(5000);

  hat.setServoDegrees(PIN_HEAD_TWIST, HEAD_TWIST_MAX);
  hat.setServoDegrees(PIN_HEAD_MOUTH, HEAD_MOUTH_MIN);

  delay(4000);
  // open & close the mouth
  hat.setServoDegrees(PIN_HEAD_MOUTH, HEAD_MOUTH_MAX);
  delay(800);
  hat.setServoDegrees(PIN_HEAD_MOUTH, HEAD_MOUTH_MIN);

  int twist_range = HEAD_TWIST_MAX - HEAD_TWIST_MIN;
  int increments = 40;
  for (int i = increments; i > 0; i--) {
    hat.setServoDegrees(PIN_HEAD_TWIST, HEAD_TWIST_MIN + (twist_range * i / increments));
    delay(150);
  }

  hat.setServoDegrees(PIN_HEAD_TWIST, HEAD_TWIST_MIN);

  delay(2000);

  openHand();

  delay(4000);

}

void closeHand() {
  hat.setServoDegrees(PIN_RIGHT_THUMB, RIGHT_THUMB_MIN);
  hat.setServoDegrees(PIN_RIGHT_INDEX, RIGHT_INDEX_MIN);
  hat.setServoDegrees(PIN_RIGHT_RING, RIGHT_RING_MIN);
  hat.setServoDegrees(PIN_RIGHT_PINKY, RIGHT_PINKY_MIN);
}

void openHand() {
  hat.setServoDegrees(PIN_RIGHT_THUMB, RIGHT_THUMB_MAX);
  hat.setServoDegrees(PIN_RIGHT_INDEX, RIGHT_INDEX_MAX);
  hat.setServoDegrees(PIN_RIGHT_RING, RIGHT_RING_MAX);
  hat.setServoDegrees(PIN_RIGHT_PINKY, RIGHT_PINKY_MAX);
}

void rollOpenAndCloseHand() {
  closeHand();
  delay(2000);
  hat.setServoDegrees(PIN_RIGHT_PINKY, RIGHT_PINKY_MAX);
  delay(200);
  hat.setServoDegrees(PIN_RIGHT_RING, RIGHT_RING_MAX);
  delay(200);
  hat.setServoDegrees(PIN_RIGHT_INDEX, RIGHT_INDEX_MAX);
  delay(200);
  hat.setServoDegrees(PIN_RIGHT_THUMB, RIGHT_THUMB_MAX);
  hat.setServoDegrees(PIN_RIGHT_PINKY, RIGHT_PINKY_MIN);
  delay(200);
  hat.setServoDegrees(PIN_RIGHT_RING, RIGHT_RING_MIN);
  delay(200);
  hat.setServoDegrees(PIN_RIGHT_INDEX, RIGHT_INDEX_MIN);
  delay(200);
  hat.setServoDegrees(PIN_RIGHT_THUMB, RIGHT_THUMB_MIN);
  
  delay(1000);
}


