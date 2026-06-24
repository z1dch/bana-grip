#include <Servo.h>

Servo myservowaist;
Servo myservoshoulder;
Servo myservoelbow;
Servo myservowristpitch;
Servo myservowristroll;
Servo myservogrip;

// Array to store current angles for each servo
int currentAngles[6] = {95, 40, 0, 170, 0, 80};

String detectedItem;

void setup() {
  Serial.begin(9600);

  myservowaist.attach(3);
  myservoshoulder.attach(5);
  myservoelbow.attach(6);
  myservowristpitch.attach(9);
  myservowristroll.attach(10);
  myservogrip.attach(11);
  delay(10);
  defaultPos();
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    detectedItem = Serial.readStringUntil('\n');
    // Check what was detected and react accordingly
    if (detectedItem == "ripe") {
      ripeSection();  // Release to the right
      delay(1000);
      defaultPos();
      delay(3000);
      Serial.println("done");  // Signal to Python that the action is complete
    } else if (detectedItem == "unripe") {
      unripeSection();  // Release to the left
      delay(1000);
      defaultPos();
      delay(3000);
      Serial.println("done");  // Signal to Python that the action is complete
    } else if (detectedItem == "overripe") {
      overripeSection();  // Release to the left
      delay(1000);
      defaultPos();
      delay(3000);
      Serial.println("done");  // Signal to Python that the action is complete
    } else if (detectedItem == "rotten") {
      rottenSection();
      delay(1000);
      defaultPos();
      delay(3000);
      Serial.println("done");  // Signal to Python that the action is complete
    } else if (detectedItem == "none") {
      defaultPos();
      Serial.println("done");  // Signal to Python that the action is complete
    } 
    
  }
}

// Function to move servo to endAngle with defined steps
void moveServoSlowly(Servo servo, int endAngle, int step, int index) {
  int startAngle = currentAngles[index];
  int increment = (startAngle < endAngle) ? step : -step;

  while ((increment > 0 && startAngle <= endAngle) || (increment < 0 && startAngle >= endAngle)) {
    servo.write(startAngle);
    delay(20); // Smaller delay for smoother movement
    startAngle += increment;
  }
  servo.write(endAngle); // Ensure servo ends at the exact target angle
  currentAngles[index] = endAngle; // Update current angle to the final target angle
}

void defaultPos() {

  moveServoSlowly(myservowristroll, 0, 5, 4);
  delay(100);
  moveServoSlowly(myservoelbow, 180, 5, 2);
  delay(100);
  moveServoSlowly(myservowristpitch, 130, 5, 3);
  delay(100);
  moveServoSlowly(myservoshoulder, 40, 5, 1);
  delay(100);
  moveServoSlowly(myservowaist, 95, 5, 0);
  delay(100);
  moveServoSlowly(myservogrip, 160, 5, 5);
  delay(100);

}

void grabObject() {
  moveServoSlowly(myservowaist, 180, 5, 0);
  delay(100);
  moveServoSlowly(myservoshoulder, 80, 1, 1);
  delay(100);
  moveServoSlowly(myservoelbow, 140, 1, 2);
  delay(100);
  moveServoSlowly(myservowristroll, 90, 2, 4);
  delay(100);
  moveServoSlowly(myservogrip, 100, 2, 5);
  delay(100);
  moveServoSlowly(myservoshoulder, 100, 1, 1);
  delay(100);
  moveServoSlowly(myservowristpitch, 160, 2, 3);
  delay(100);
  moveServoSlowly(myservoshoulder, 120, 1, 1);
  delay(100);
  moveServoSlowly(myservogrip, 145, 5, 5);
  delay(100);
  moveServoSlowly(myservowristroll, 0, 1, 4);
  delay(100);
  moveServoSlowly(myservoshoulder, 70, 1, 1);
  delay(100);
  moveServoSlowly(myservoelbow, 140, 1, 2);
  delay(100);
  moveServoSlowly(myservoshoulder, 40, 1, 1);
  delay(100);
  defaultPos();
}

void releaseObject() {
  moveServoSlowly(myservoshoulder, 70, 2, 1);
  delay(100);
  moveServoSlowly(myservoelbow, 140, 1, 2);
  delay(100);
  moveServoSlowly(myservowristroll, 90, 2, 4);
  delay(100);
  moveServoSlowly(myservoshoulder, 110, 2, 1);
  delay(100);
  moveServoSlowly(myservogrip, 90, 2, 5);
  delay(100);
  moveServoSlowly(myservoshoulder, 70, 2, 1);
  delay(100);
  moveServoSlowly(myservoelbow, 180, 1, 2);
  delay(100);
  moveServoSlowly(myservoshoulder, 40, 2, 1);
  delay(100);
  defaultPos();
}

void ripeSection() {
  grabObject();
  moveServoSlowly(myservowaist, 100, 2, 0);
  delay(100);
  releaseObject();
}

void unripeSection() {
  grabObject();
  moveServoSlowly(myservowaist, 115, 2, 0);
  delay(100);
  releaseObject();
}

void overripeSection() {
  grabObject();
  moveServoSlowly(myservowaist, 85, 2, 0);
  delay(100);
  releaseObject();
}
void rottenSection() {
  grabObject();
  moveServoSlowly(myservowaist, 65, 2, 0);
  delay(100);
  releaseObject();
}