#include "servoControll.h"

void setServoPosition(float spotPrice, Servo &myServo) {
  if (spotPrice > 100) {
    // Set the servo position to 180 degrees
    myServo.write(120);
  } else {
    // Set the servo position to 0 degrees
    myServo.write(30);

  }
}