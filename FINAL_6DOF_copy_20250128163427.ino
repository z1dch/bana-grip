#include <Servo.h>

  // Define servos of each part of robotic arm
  Servo servoWAIST;
  Servo servoSHOULDER;
  Servo servoELBOW;
  Servo servoWRISTPITCH;
  Servo servoWRISTROLL;
  Servo servoGRIPPER;

  String inputString;

  const byte A_good = 0;
  const byte A_bad = 1;
  const byte B_good = 2;
  const byte B_bad = 3;
  const byte C_good = 4;
  const byte C_bad = 5;
  const byte D_good = 6;
  const byte D_bad = 7;
  const byte default_pos = 8;
  byte detect_object;

  // Smooth movement function
  void moveServoSmoothly(Servo &servo, int startAngle, int endAngle, int stepDelay) {
    if (startAngle < endAngle) {
      for (int angle = startAngle; angle <= endAngle; angle++) {
        servo.write(angle);
        delay(stepDelay);
      }
    } else {
      for (int angle = startAngle; angle >= endAngle; angle--) {
        servo.write(angle);
        delay(stepDelay);
      }
    }
  }

  // Initialize positions
  void initializePosition() {
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 90, 20);
    delay(100);
    moveServoSmoothly(servoWRISTPITCH, servoWRISTPITCH.read(), 140, 20);
    delay(100);    
       moveServoSmoothly(servoELBOW, servoELBOW.read(), 50, 20);
    delay(100);
    moveServoSmoothly(servoSHOULDER, servoSHOULDER.read(), 20, 20);
    delay(100);
    moveServoSmoothly(servoWRISTROLL, servoWRISTROLL.read(), 90, 20);
    delay(100);    
    moveServoSmoothly(servoGRIPPER, servoGRIPPER.read(), 90, 20);
    delay(100);
  }

  void backtocentralPosition() {
        moveServoSmoothly(servoWRISTPITCH, servoELBOW.read(), 10, 20); //pataas
    delay(3000);
    moveServoSmoothly(servoWRISTPITCH, servoWRISTPITCH.read(), 10, 20); //pataas
    delay(3000);
        moveServoSmoothly(servoWAIST, servoWAIST.read(), 90, 20);
    delay(1000);
  }


  void D_backtocentralPosition() {
         moveServoSmoothly(servoSHOULDER, servoSHOULDER.read(), 70, 65);
    delay(500);
      moveServoSmoothly(servoWRISTPITCH, servoWRISTPITCH.read(), 40, 30);
    delay(500);
      moveServoSmoothly(servoELBOW, servoELBOW.read(), 160, 40);
    delay(500);
    moveServoSmoothly(servoWRISTPITCH, servoWRISTPITCH.read(), 10, 30);
    delay(500);
      moveServoSmoothly(servoELBOW, servoELBOW.read(), 170, 40);
    delay(500);
    moveServoSmoothly(servoSHOULDER, servoSHOULDER.read(), 150, 60);
    delay(500);
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 90, 30);
    delay(500);
  }

  void goodContainer() {
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 40, 20);
    delay(500);
  }

  void badContainer() {
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 5, 20);
    delay(500);
  }

  void releaseBanana() {
    moveServoSmoothly(servoGRIPPER, servoGRIPPER.read(), 20, 20);
    delay(1000);
  }

  void holdBanana() {
    moveServoSmoothly(servoGRIPPER, servoGRIPPER.read(), 170, 20);
    delay(1000);
  }

  void pick_A () {
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 165, 40);
    delay(1000);
    moveServoSmoothly(servoSHOULDER, servoSHOULDER.read(), 90, 40);
    delay(1000);
    moveServoSmoothly(servoWRISTPITCH, servoWRISTPITCH.read(), 110, 40);
    delay(1000);
    moveServoSmoothly(servoELBOW, servoELBOW.read(), 60, 40);
    delay(1000);
  }

  void pick_B () {
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 150, 40);
    delay(1000);
    moveServoSmoothly(servoSHOULDER, servoSHOULDER.read(), 90, 40);
    delay(1000);
    moveServoSmoothly(servoWRISTPITCH, servoWRISTPITCH.read(), 100, 40);
    delay(1000);
    moveServoSmoothly(servoELBOW, servoELBOW.read(), 60, 40);
    delay(1000);
  }


  void pick_C () {
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 140, 40);
    delay(1000);
     moveServoSmoothly(servoWRISTROLL, servoWRISTROLL.read(), 45, 40);
    delay(1000);
    moveServoSmoothly(servoSHOULDER, servoSHOULDER.read(), 115, 40);
    moveServoSmoothly(servoELBOW, servoELBOW.read(), 65, 40);
    delay(1000);
    moveServoSmoothly(servoWRISTPITCH, servoWRISTPITCH.read(), 90, 40);
    delay(1000);

  }

  void pick_D () {
    moveServoSmoothly(servoWRISTROLL, servoWRISTPITCH.read(), 70, 15);
    delay(500);
    moveServoSmoothly(servoWAIST, servoWAIST.read(), 135, 15);
    delay(500);
      moveServoSmoothly(servoELBOW, servoELBOW.read(), 120, 30);
    delay(500);
    moveServoSmoothly(servoSHOULDER, servoSHOULDER.read(), 175, 75);
    delay(500);
  }


  void setup() {
    Serial.begin(9600);
    // Attach servos to respective pins
    delay(2000);
      servoWRISTPITCH.attach(9);
    servoELBOW.attach(6);
    servoSHOULDER.attach(5);
    servoWAIST.attach(3);
    servoWRISTROLL.attach(10);
    servoGRIPPER.attach(11);
    //CENTRAL POSITION
    initializePosition();
  }

  void loop() {
  // Check for incoming serial data
    if (Serial.available() > 0) {
      inputString = Serial.readStringUntil('\\n'); // Read the input string until a newline character
      inputString.trim(); // Remove any leading/trailing whitespace

      // Convert input string to corresponding detect_object value
      if (inputString == "A 1") {
        detect_object = A_good;
      } else if (inputString == "A 0") {
        detect_object = A_bad;
      } else if (inputString == "B 1") {
        detect_object = B_good;
      } else if (inputString == "B 0") {
        detect_object = B_bad;
      } else if (inputString == "C 1") {
        detect_object = C_good;
      } else if (inputString == "C 0") {
        detect_object = C_bad;
      } else if (inputString == "D 1") {
        detect_object = D_good;
      } else if (inputString == "D 0") {
        detect_object = D_bad;
      } else {
        detect_object = default_pos;
      }

      // Handle the action based on detect_object
      switch (detect_object) {
        case A_good:
          Serial.println("PICK A - GOOD");
          //PICK A - GOOD
    delay(1000);
    releaseBanana();
    pick_A();
    holdBanana();
    backtocentralPosition();
    goodContainer();
    releaseBanana();
    initializePosition();
          break;
        case A_bad:
          Serial.println("PICK A - BAD");
            //PICK A - BAD
    releaseBanana();
    pick_A();
    holdBanana();
    backtocentralPosition();
    badContainer();
    releaseBanana();
    initializePosition();
          break;
        case B_good:
          Serial.println("PICK B - GOOD");
            //PICK B - GOOD
    releaseBanana();
    pick_B();
    holdBanana();
    backtocentralPosition();
    goodContainer();
    releaseBanana();
    initializePosition();
          break;
        case B_bad:
          Serial.println("PICK B - BAD");
            // //PICK B - BAD
    releaseBanana();
    pick_B();
    holdBanana();
    backtocentralPosition();
    badContainer();
    releaseBanana();
    initializePosition();

          break;
        case C_good:
          Serial.println("PICK C - GOOD");
            //PICK C - GOOD
    releaseBanana();
    pick_C();
    holdBanana();
    backtocentralPosition();
    goodContainer();
    releaseBanana();
    initializePosition();

          break;
        case C_bad:
          Serial.println("PICK C - BAD");
            // //PICK C - BAD
    releaseBanana();
    pick_C();
    holdBanana();
    backtocentralPosition();
    badContainer();
    releaseBanana();
    initializePosition();
  
          break;
        case D_good:
          Serial.println("PICK D - GOOD");
        
          //PICK D - GOOD
    releaseBanana();
    pick_D();
    holdBanana();
    D_backtocentralPosition();
    goodContainer();
    releaseBanana();
    initializePosition();

          break;
        case D_bad:
          Serial.println("PICK D - BAD");
            // //PICK D - BAD
    // releaseBanana();
    // pick_D();
    // holdBanana();
    // D_backtocentralPosition();
    // badContainer();
    // releaseBanana();
    // initializePosition();

          break;
        case default_pos:
          Serial.println("CENTRAL POSITION");
          initializePosition ();
          break;
      }

      // Clear the inputString after processing
      inputString = "";
    }
      //detach all parts
    // servoWRISTPITCH.detach();
    // servoELBOW.detach();
    // servoSHOULDER.detach();
    // servoWAIST.detach();
    // servoWRISTROLL.detach();
    // servoGRIPPER.detach();
  }