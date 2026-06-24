#include <Servo.h>

Servo servo1, servo2, servo3, servo4, servo5, servo6;

void setDefaultPositions();
void turnLeft();
void turnRight();
void goDown();
void goDown2();
void openPosition();
void closePosition();
void scanPosition();
void middlePosition();
void grabPosition();
void gradualDelay(int milliseconds);

String command;

void setup() {
  Serial.begin(9600);
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);

  setDefaultPositions();
}

void loop() {

  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    //char command = Serial.read();
    if (command == "L" || command == 'l') {
      turnLeft();
    } else if (command == "L2" || command == 'l2') {
      turnLeft2();
    } else if (command == "R" || command == 'r') {
      turnRight();
    } else if (command == "D" || command == 'd') {
      goDown();
    } else if (command == "F" || command == 'f') {
      forwardPosition();
    } else if (command == "F2" || command == 'f2') {
      forwardPosition2();
    } else if (command == "F3" || command == 'f2') {
      forwardPosition3();
    } else if (command == "S" || command == 's') {
      setDefaultPositions();
    } else if (command == "O" || command == 'o') {
      openPosition();
    } else if (command == "C" || command == 'c') {
     closePosition();
    } else if (command == "A" || command == 'a') {
      rotateGripper();
    } else if (command == "M" || command == 'm') {
      middlePosition();
    } else if (command == "G" || command == 'g') {
      rotateGripper2();
    } else if (command == "G2" || command == 'g2') {
     getPosition();
    } else if (command == "G3" || command == 'g3') {
     getPosition3();
    }else if (command == "green" || command == 'green') {
     greenSection();
     gradualDelay(1000);
    }else if (command == "red" || command == 'red') {
     redSection();
     gradualDelay(1000);
    }else if (command == "rotten" || command == 'rotten') {
     rottenSection();
     gradualDelay(1000);
    }else if (command == "U" || command == 'u') {
     goUp();
    }else if (command == "P" || command == 'p') {
     goUp1();
    } else if (command == "none" || command == 'none') {
      setDefaultPositions();
    }
    Serial.println("done");

  }
}

void setDefaultPositions() {
  servo2.write(110);
  gradualDelay(15);
  servo3.write(125);
  gradualDelay(15);
  servo4.write(160);
  gradualDelay(15);
}

void turnLeft() {
  for (int pos = servo1.read(); pos <= 150; pos += 1) {
    servo1.write(pos);
    gradualDelay(15); 
  }
}

void turnLeft2() {
  for (int pos = servo1.read(); pos <= 130; pos += 1) {
    servo1.write(pos);
    gradualDelay(15); 
  }
}

void turnRight() {
  int initialPos = servo1.read();
  for (int pos = initialPos; pos >= 45; pos -= 1) {
    servo1.write(pos);
    gradualDelay(15);
  }
}

void forwardPosition() {
  int currentPos = servo2.read();
    if (currentPos > 125) {
      for (int pos = currentPos ; pos >= 125; pos -= 1) {
        servo2.write(pos);
        gradualDelay(15); 
      } 

    }else {
      for (int pos = currentPos ; pos <= 125; pos += 1) {
        servo2.write(pos);
        gradualDelay(15); 
    }
  }
}
void forwardPosition3() {
  int currentPos = servo2.read();
    if (currentPos > 175) {
      for (int pos = currentPos ; pos >= 175; pos -= 1) {
        servo2.write(pos);
        gradualDelay(15); 
      } 

    }else {
      for (int pos = currentPos ; pos <= 175; pos += 1) {
        servo2.write(pos);
        gradualDelay(15); 
    }
  }
}
void getPosition() {
  int currentPos = servo3.read();
    if (currentPos > 140) {
      for (int pos = currentPos ; pos >= 140; pos -= 1) {
        servo3.write(pos);
        gradualDelay(15); 
      } 

    }else {
      for (int pos = currentPos ; pos <= 140; pos += 1) {
        servo3.write(pos);
        gradualDelay(15); 
    }
  }
}
void getPosition3() {
  int currentPos = servo3.read();
    if (currentPos > 170) {
      for (int pos = currentPos ; pos >= 170; pos -= 1) {
        servo3.write(pos);
        gradualDelay(15); 
      } 

    }else {
      for (int pos = currentPos ; pos <= 170; pos += 1) {
        servo3.write(pos);
        gradualDelay(15); 
    }
  }
}
void forwardPosition2() {
  int currentPos = servo2.read();
    if (currentPos > 165) {
      for (int pos = currentPos ; pos >= 165; pos -= 1) {
        servo2.write(pos);
        gradualDelay(15); 
      } 

    }else {
      for (int pos = currentPos ; pos <= 165; pos += 1) {
        servo2.write(pos);
        gradualDelay(15); 
    }
  }
}

void middlePosition() {
  int currentPos = servo1.read();
  
  if (currentPos > 90) {
    for (int pos = currentPos; pos >= 90; pos -= 1) {
      servo1.write(pos);
      gradualDelay(15);
    }
  } else {
    for (int pos = currentPos; pos <= 90; pos += 1) {
      servo1.write(pos);
      gradualDelay(15);
    }
  }
}

void goDown() {
  for (int pos = servo4.read(); pos >= 30; pos -= 1) {
    servo4.write(pos);
    gradualDelay(15); 
  }
  for (int pos = servo3.read(); pos >= 5; pos -= 1) {
    servo3.write(pos);
    gradualDelay(15); 
  }
  for (int pos = servo2.read(); pos <= 85; pos += 1) {
    servo2.write(pos);
    gradualDelay(15); 
  }
}
void goUp() {
  int currentPos = servo4.read();
    if (currentPos > 70) {
      for (int pos = currentPos ; pos >= 70; pos -= 1) {
        servo4.write(pos);
        gradualDelay(15); 
      } 

    }else {
      for (int pos = currentPos ; pos <= 70; pos += 1) {
        servo4.write(pos);
        gradualDelay(15); 
    }
  }
}
void goUp1() {
  int currentPos = servo2.read();
    if (currentPos > 130) {
      for (int pos = currentPos ; pos >=130 ; pos -= 1) {
        servo3.write(pos);
        gradualDelay(15); 
      } 

    }else {
      for (int pos = currentPos ; pos <= 130; pos += 1) {
        servo3.write(pos);
        gradualDelay(15); 
    }
  }
}
void grab() { //grab for ALL CHILI
 forwardPosition();
 delay(500);
 getPosition();
 delay(500);
 openPosition();
 delay(500);
 forwardPosition2();
 delay(500);
 closePosition();
 delay(500);
 setDefaultPositions();
 delay(500);
}

void left1() {
 turnLeft();
}
void left2() {
 turnLeft2();
}
void right() {
  turnRight();
}
void greenSection() {
 grab();
 delay(500);
 left1();
 delay(500);
 release();
}
void redSection() {
 grab();
 delay(500);
 right();
 delay(500);
 release();
}
void rottenSection() {
 grab();
 delay(500);
 left2();
 delay(500);
 release2();
}

void release() { //release for GREEN AND RED CHILI
forwardPosition();
delay(500);
openPosition();
delay(500);
setDefaultPositions();
delay(500);
middlePosition();
delay(500);
closePosition();
delay(500);
}

void release2() { //release for ROTTEN CHILI
forwardPosition();
delay(500);
getPosition3();
delay(500);
forwardPosition3();
delay(500);
openPosition();
delay(500);
goUp();
delay(500);
goUp1();
delay(500);
setDefaultPositions();
delay(500);
middlePosition();
delay(500);
closePosition();
delay(500);
}

// void goUp1(){
//     int currentPos = servo2.read();

//   if (currentPos > 110) {
//     for (int pos = currentPos; pos >= 110; pos -= 1) {
//       servo2.write(pos);
//       gradualDelay(15);
//     }
//   } else {
//     for (int pos = currentPos; pos <= 110; pos += 1) {
//       servo2.write(pos);
//       gradualDelay(15);
//     } 
//   }
// }
// void goUp2(){
//       int currentPos2 = servo3.read();
//   if (currentPos2 > 125) {
//     for (int pos = currentPos2; pos >= 125; pos -= 1) {
//       servo3.write(pos);
//       gradualDelay(15);
//     }
//   } else {
//     for (int pos = currentPos2; pos <= 125; pos += 1) {
//       servo3.write(pos);
//       gradualDelay(15);
//     }
//   }
// }
// void goUp3(){
//       int currentPos3 = servo4.read();
//   if (currentPos3 > 160) {
//     for (int pos = currentPos3; pos >= 160; pos -= 1) {
//       servo4.write(pos);
//       gradualDelay(15);
//     }
//   } else {
//     for (int pos = currentPos3; pos <= 160; pos += 1) {
//       servo4.write(pos);
//       gradualDelay(15);
//     }
//   }
// }

// void goUp() {
//   goUp1();
//   gradualDelay(15);
//   goUp2();
//   gradualDelay(15);
//   goUp3();
//   gradualDelay(15);


  //servo2.write(110);
  //gradualDelay(15);
  //servo3.write(125);
  //gradualDelay(15);
  //servo4.write(160);
  //gradualDelay(15);
//}

// void goDown2() {
//   for (int pos = servo4.read(); pos >= 45; pos -= 1) {
//     servo4.write(pos);
//     gradualDelay(15); 
//   }
//   for (int pos = servo3.read(); pos >= 15; pos -= 1) {
//     servo3.write(pos);
//     gradualDelay(15); 
//   }
//   for (int pos = servo2.read(); pos <= 75; pos += 1) {
//     servo2.write(pos);
//     gradualDelay(15); 
//   }
// }

void openPosition() {
  for (int pos = servo6.read(); pos >= 30; pos -= 1) {
    servo6.write(pos);
    gradualDelay(15);
  }
}

void closePosition() {
  for (int pos = servo6.read(); pos <= 90; pos += 1) {
    servo6.write(pos);
    gradualDelay(15); 
  }
}

void rotateGripper() {
  for (int pos = servo5.read(); pos >= 0; pos -= 1) {
    servo5.write(pos);
    gradualDelay(15); 
  }
}

void rotateGripper2() {
  for (int pos = servo5.read(); pos <= 180; pos += 1) {
    servo5.write(pos);
    gradualDelay(15); 
  }
}

void gradualDelay(int milliseconds) {
  int steps = milliseconds / 15;
  for (int i = 0; i < steps; ++i) {
    delay(15);
  }
}
