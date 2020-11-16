#ifndef StepperMotorClass_h
#define StepperMotorClass_h

#include "Arduino.h"
#include "A4988Class.h"
#include "limitSwitchClass.h"

class stepperMotor
{
  public:
    stepperMotor(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin, uint8_t limitSwitchPin);
    void initialize();
    void moveDistance(int distance);
    void moveUp();
    void moveDown();
    void home();

    void moveDownGripper();
    void moveDistanceGripper(int distance);
    void homeGripper();


    void holdingTorque(bool state);

    void status();

    int maxDistance = 100;
    int maxDistanceGripper = 7.325; //[mm]
    int limitSwitchOffset = 10;


  private:

    uint8_t _stepPin;
    uint8_t _dirPin;
    uint8_t _enablePin;
    uint8_t _limitSwitchPin;

    float _currentPosition = 0;
    uint8_t _stepsPerRev = 200;
    uint8_t _mmPerRev = 2;
    float _mmPerStep = (float)_mmPerRev/_stepsPerRev;
    ////////////////////////////////////////////////
    //GRIPPER
    uint8_t _stepsPerRev = 300;
    //uint8_t _mmPerRev = 2;
    float _mmPerStep = (float)_mmPerRev/_stepsPerRev;
    ////////////////////////////////////////////////////////
    int _numberOfSteps;

    int _distanceToSteps(int distance);
    void _updateCurrentPosition(int distance);
    void _moveCW();
    void _moveCCW();
    bool _withinBoundaries();

    int _distanceToStepsGripper(int distance);

    A4988 _A4988;
    limitSwitch _limitSwitch;

};

#endif
