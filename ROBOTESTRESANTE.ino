#include <AFMotor.h>
#include <NewPing.h>

#include <Servo.h>

#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo myservo;

AF_DCMotor motor1 ( 1 );
AF_DCMotor motor2 ( 2 );
//AF_DCMotor motor3 ( 2 );
//AF_DCMotor motor4 ( 3 );

void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
//  motor3.setSpeed(255);
//  motor3.run(RELEASE);
//  motor4.setSpeed(255);
//  motor4.run(RELEASE);
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
}


void loop() {
  // put your main code here, to run repeatedly:

//  digitalWrite(5, HIGH);
//  digitalWrite(4, LOW);

int distance = sonar.ping_cm();
if (distance <= 10) {
  myservo.write(0);
  if (sonar.ping_cm() > 10) {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(1000);
  }
  else {
    myservo.write(180);
    if (sonar.ping_cm() > 10) {
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      delay(1000);
    }
    else {
      while (true) {
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        delay(1000);
      }
    }
  }
}
else {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
//motor3.run(FORWARD);
//motor4.run(FORWARD);

}
