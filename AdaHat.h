
#ifndef AdaHat_h
#define AdaHat_h


#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"


class AdaHat {

  private:
    Adafruit_PWMServoDriver _pwm;

    // safe defaults if something else goes wrong, aka 90 degrees
    int _servoMins[16] = { 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375 };
    int _servoMaxs[16] = { 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375, 375 };

  public:
    AdaHat(int boardPosition);
    void setup();
    void setupServo(int position, int min, int max);
    void setServoDegrees(int position, int degrees);
  
};

#endif

