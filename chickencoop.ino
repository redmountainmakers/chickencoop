int FWD = 4;
int REV = 5;
int LIGHT = 0;

int CLOSE_SWITCH = 8;
int OPEN_SWITCH = 9;

void setup() {
  pinMode( FWD, OUTPUT);
  pinMode( REV, OUTPUT);
  pinMode( CLOSE_SWITCH, INPUT);
  pinMode( OPEN_SWITCH, INPUT);
  Serial.begin( 9600);
  stopMotor();
  openDoor();
}

void loop() {
  static int daylight=true;
  if ( daylight) {
    daylight = checkDaylight();
    if ( !daylight) { // switch from daylight to !daylight
      closeDoor();
    }
  } else {
    daylight = checkDaylight();
    if ( daylight) { // switch from !daylight to daylight
      openDoor();
    }
  }
  delay( 1000); // wait a second before checking again
}

int checkOpen() {
  return digitalRead( OPEN_SWITCH);
}

int checkClosed(){
  return digitalRead( CLOSE_SWITCH);
}

int checkDaylight() {
  int light = analogRead( LIGHT);
  if ( light > 300) {
    return true;  // light level above 300 ==> daylight
  } else {
    return false; // light level below/equal 300  ==> night
  }
}

void stopMotor() { // set hbridge stop
  Serial.println( "stopMotor");
  digitalWrite( FWD,LOW);
  digitalWrite( REV,LOW);
}

void closeDoor() {
  Serial.println( "closeDoor");

  int doorClosed = checkClosed();
  if ( !doorClosed) motorForward(); // if not closed run motor forward
  
  while( !doorClosed) {
    doorClosed = checkClosed();  // keep checking closed status
  }

  stopMotor(); // stop motor after close status detected
}

void openDoor() {
  Serial.println( "openDoor");
  
  int doorOpen = checkOpen();
  if ( !doorOpen) motorReverse(); // if not open run motor backward
  
  while( !doorOpen) {
    doorOpen = checkOpen(); // keep checking open status
  }

  stopMotor(); // stop motor after open status detected
}

void motorReverse() { // set hbridge reverse
  digitalWrite( FWD,LOW);
  digitalWrite( REV,HIGH);
}

void motorForward() { // set hbridge forward
  digitalWrite( FWD,HIGH);
  digitalWrite( REV,LOW);
}
