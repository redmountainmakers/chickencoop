int FWD = 4;
int REV = 5;
int LIGHT = 0;

int CLOSE_SWITCH = 8;
int OPEN_SWITCH = 9;

void setup() {
  pinMode(FWD, OUTPUT);
  pinMode(REV, OUTPUT);
  pinMode(CLOSE_SWITCH, INPUT);
  pinMode(OPEN_SWITCH, INPUT);
  Serial.begin(9600);
  stopMotor();
  openDoor();
}

//void loop() {
  //openDoor();
  //delay(1000);
//}



void loop() {
  static int daylight=true;
  if (daylight) {
    daylight = checkDaylight();
    if (!daylight) {
      closeDoor();
    }
  } else {
    daylight = checkDaylight();
    if (daylight) {
      openDoor();
    }
  }
  delay(1000);
}

int checkOpen() {
  return digitalRead(OPEN_SWITCH);
}

int checkClosed(){
  return digitalRead(CLOSE_SWITCH);
}

int checkDaylight() {
  int light = analogRead(LIGHT);
  if (light>300) {
    return true;
  } else {
    return false;
  }
}

void stopMotor() {
  Serial.println("stopMotor");
  digitalWrite(FWD,LOW);
  digitalWrite(REV,LOW);
}

void closeDoor() {
  Serial.println("closeDoor");
  int doorClosed = checkClosed();

  if (!doorClosed) motorForward();
  
  while(!doorClosed) {
    doorClosed = checkClosed();
  }
  stopMotor();
}

void openDoor() {
  int doorOpen = checkOpen();
  Serial.println("openDoor");
  
  if (!doorOpen) motorReverse();
  
  while(!doorOpen) {
    doorOpen = checkOpen();
  }
  stopMotor();
}

void motorReverse() {
  digitalWrite(FWD,LOW);
  digitalWrite(REV,HIGH);
}

void motorForward() {
  digitalWrite(FWD,HIGH);
  digitalWrite(REV,LOW);
}
