// ============================================================
//
// CBP_Layer.ino  29-08-17
//
// Middle layer for Comp1811 Stepper Motor Robots
//
// ============================================================

int stepsL, stepsR; // nr of steps to take for Left/Right motor
int dirL, dirR;     // direction of Left/Right motors
boolean firstPassF = true;
boolean firstPassR = true;

// Call to set the motor speed
void setupSteppers(int speed) {
  stepperR.setSpeed(speed);
  stepperL.setSpeed(speed);
}

void resetMotors() {
  firstPassF = true;
  firstPassR = true;
}
// applies a single step to each motor in appropriate dirn.
boolean goForwards(float dist) {
  boolean done;
  if(firstPassF) {
     firstPassF = false; 
     prepMoveForward(dist);
  }
  if(stepsR != 0) {
    stepperR.step(dirR);
    stepsR -= 1;    
  }
  if(stepsL != 0) {
    stepperL.step(dirL); 
    stepsL -= 1;    
  }
  done = getMotorsDone();
  if(done) firstPassF = true;
  return done;
}
boolean doRotate(float angle) {
  boolean done;
  if(firstPassR) {
     firstPassR = false; 
     prepRotate(angle);   
  }
  if(stepsR != 0) {
    stepperR.step(dirR);
    stepsR -= 1;    
  }
  if(stepsL != 0) {
    stepperL.step(dirL); 
    stepsL -= 1;    
  }
  done = getMotorsDone();
  if(done) firstPassR = true;
  return done;
}

// applies a single step to each motor in appropriate dirn.
void driveMotors() {
  if(stepsR != 0) {
    stepperR.step(dirR);
    stepsR -= 1;    
  }
  if(stepsL != 0) {
    stepperL.step(dirL); 
    stepsL -= 1;    
  }
}

// Call to prepare to move forward. 
void prepMoveForward(float dist) {
  stepsL = (int)(scalingFwd*dist);
  stepsL = abs(stepsL);
  stepsR = stepsL;
  if(dist < 0) {
    dirL = -1;
    dirR = 1;    
  } else {
    dirL = 1;
    dirR = -1;    
  }
}

// Call to prepare to rotate. 
void prepRotate(float degrees) { 
  stepsR = (int)(degrees*scalingRot);
  stepsR = abs(stepsR);
  stepsL = stepsR;
  if(degrees > 0) {
    dirL = 1;
    dirR = 1;
  } else {
    dirL = -1;
    dirR = -1;    
  }
}

// Call to stop motors
void stopMotors() {
  stepsL = 0;
  stepsR = 0;
}

// Returns true when both motors have no remaining steps to exe
boolean getMotorsDone() {
  if( (stepsR == 0) && (stepsL ==0))
    return true;
  else 
    return false;
}
