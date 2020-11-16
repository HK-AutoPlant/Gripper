#include "Classes/StepperMotorGripperClass.h"
#include "Classes/limitSwitchClass.h"

#define BAUD_RATE 115200

uint8_t dirPin    = 2;
uint8_t stepPin   = 3;
uint8_t enablePin = 4;
uint8_t UpperlimitSwitchPin = 5;
uint8_t SensorlimitSwitchPin = 6;

ModifiedSteppermotor Gripper(uint8_t stepPin, uint8_t dirPin,
  uint8_t enablePin, uint8_t UpperlimitSwitchPin);
limitSwitch Sensor(uint8_t SensorlimitSwitchPin);

int d = 7.325; //[mm]
int soil;


void setup() {

    Serial.begin(9600);

    //Serial.begin(BAUD_RATE);
    Gripper.initialize();
    Sensor.initialize();
}


void loop() {
  if (Serial.available() > 0){
    int msg = Serial.read();

    Switch (msg) {
      case 'g' //Grip the plants
        if(Sensor.isPressed() == true){
          soil = 1; //save value that a tree exists in the slot
          Signal.print('Soil detected');
          Gripper.moveDownGripper(); //Gripp the tree
          Gripper.holdingTorque(true); //hold
          Serial.write('Gripped'); //message to gantry
        }
        else {
          soil = 0; // Assumes there is no tree in that specific tray
          Signal.print('no soil detected');
        }
        //Missing:  an elseif for when all elements in soil-vector (not vector yet) is zero.
        //          In this function, the message 'Redo' will be written so that case 'g' is executed again.
      break;

      case 'c' //check check if plant has slipped
        if(soil == 1){
          if(Sensor.isPresssed() == true){
            soil = 1;
            Signal.print('Soil still detected');
          }
          else {
            Signal.print('No soil detected/Tree has slipped');
            soil = 0;
            Gripper.homeGripper(); //Gripper releases the plants
            Serial.write('Redo'); //sends message so the gantry moves down
          }
        }
      break;

      case 'r' //release the plants
        Gripper.homeGripper(); //Gripper releases the plants
        Serial.write('plants released'); //msg to gantry
      break;
    }
  }
}

//question: should it only check and redo if the soil was detected the first
//time or should it ignor the first test?
