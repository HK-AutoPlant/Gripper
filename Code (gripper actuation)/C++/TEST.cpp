#define BAUD_RATE 115200

//just for Gripper

//Pins
uint8_t dirPin    = 2;
uint8_t stepPin   = 3;
uint8_t enablePin = 4;
uint8_t UpperlimitSwitchPin = 5;
uint8_t SensorlimitSwitchPin = 6;

int earth;
int Plants;

int steps = 200; //needs calculation
int offset = 10; // random number at this point
float pulseDelay = 500;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(UpperlimitSwitchPin, INPUT);
  pinMode(SensorlimitSwitchPin, INPUT);

  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);
  digitalWrite(enablePin, HIGH);
}

void loop() {
  earth = digitalRead(SensorlimitSwitchPin); //check sensor limit switch

  if(earth == LOW) //earth detected
  {
    Serial.print('Earth detected');
    //move down = Gripp
    digitalWrite(dirPin, HIGH);
    digitalWrite(enablePin, LOW);
    for(int i = 0; i < steps; i++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulseDelay);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(pulseDelay);
    }
    Plants = 1; //Plants gripped
    Serial.print('Plants Gripped');

    earth = digitalRead(SensorlimitSwitchPin); //check the earth

  if(earth == LOW) //check if there has been removed from tray
  {
    Serial.print('Earth detected');
    digitalWrite(enablePin, LOW); //Holding torque (keep gripping the plant)
  }
  else {
    Serial.print('Earth NOT detected');
    //move up = release plants
    digitalWrite(dirPin, LOW); //move CCW
    digitalWrite(enablePin, LOW);
    while(digitalRead(UpperlimitSwitchPin) == HIGH){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulseDelay);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(pulseDelay);
    }
    digitalWrite(enablePin, HIGH);
    //Try gripping again
    digitalWrite(dirPin, HIGH);
    digitalWrite(enablePin, LOW);
    for(int i = 0; i < steps; i++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulseDelay);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(pulseDelay);
    }
    Plants = 1; //Plants gripped
    Serial.print('Plants Gripped');
    digitalWrite(enablePin, LOW); //Holding torque
  }

    delay(1000); //in reality this is supposed to be a signal from gantry

    //release plants and move motor to home position
    digitalWrite(dirPin, LOW); //move CCW
    digitalWrite(enablePin, LOW);
    while(digitalRead(UpperlimitSwitchPin) == HIGH){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulseDelay);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(pulseDelay);
    }
    digitalWrite(enablePin, HIGH);
    delay(500);
    digitalWrite(dirPin, HIGH);
    digitalWrite(enablePin, LOW);
    for(int i = 0; i < offset; i++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pulseDelay);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(pulseDelay);
    }
    digitalWrite(enablePin, HIGH);

    Plants = 0; //platnts released
    Serial.print('Plants released');
}
else {
  Serial.print('Earth not detected');
}
}
