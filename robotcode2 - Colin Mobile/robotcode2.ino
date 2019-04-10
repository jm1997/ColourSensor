// ===========================================================
//
// Obstacle_Avoid_New_Simple
//
// CBP 07-11-17 Comp2303 Design-Build-Test Project
// 
// ===========================================================


#include <Stepper.h>

#define STATE_NULL -1
// Some names of states. You can remove these and use your own
#define WAITING 0
#define WANDER_FORWARD_1  2
#define WANDER_FORWARD_2  3
#define WANDER_FORWARD_3  4
#define WANDER_TURNRIGHT  5
#define WANDER_TURNLEFT  6
#define AVOID_BACK  7
#define AVOID_TURNRIGHT 8
#define WANDER_TURNLEFT2 9
#define WANDER_TURNLEFT3 1    
#define WANDER_BACKWARD_1 10
#define AVOID_ROTATE 11

// Transmit and Receive pins for Ultrasonic Sensor
#define TxPin A4
#define RxPin A5

int digitalPin12  =12 ;

// variables for sensor calculations

// Variable for the motor
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// Some general variables ------------------------
int state,prevState;
boolean done;
boolean collided = false;

float scalingFwd, scalingRot;

// Stuff for Ultrasonic Sensor -------------------
float obstacleDist;
float distThreshold;
unsigned long prevMillis;
long travelTime;
float distTo;

// initialize the stepper library on pins 8 through 11:
Stepper stepperL(stepsPerRevolution, 4, 6, 5, 7);
Stepper stepperR(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Calculate scaling for a particular robot
  scalingFwd = 2048/(4.8*PI);  
  scalingRot = (2048*7.5)/(4.8*180);  
  setupSteppers(20); // Slow speed for testing Could set to
  // max speed you found by experiment
  pinMode(TxPin, OUTPUT); 
  pinMode(RxPin, INPUT);   
  Serial.begin(9600);
  prevState = STATE_NULL; // Used to print out state changes
  state = WAITING;
  distThreshold = 10;     // Ultrasonic detection dist (cm)
  prevMillis = millis();  // To schedule US detection
  pinMode(12,OUTPUT);

  resetMotors();
  
}

// --------------------------------------------------------
void loop() {

  distTo = getODist();
  if(distTo < distThreshold) {
   resetMotors();   
   state = AVOID_BACK;
  }
  
  // Finite State Machine
  switch(state) {
    
    case WAITING:
      delay(1000);
      state = WANDER_FORWARD_1; //run wander state when finished
    break;

    //wander state
     case WANDER_FORWARD_1:
       done = goForwards(-10.0); 
       if(done) state = WANDER_TURNLEFT; //run turn left state when finished
     break;

     //turn left
     case WANDER_TURNLEFT:
       done= doRotate(45.0);  //angle is half of what it should be
       if(done) state = WANDER_FORWARD_1;
     break;

     case WANDER_FORWARD_3:
       done = goForwards(-10.0); 
       if(done) state = WANDER_TURNLEFT;
     break;

     case WANDER_TURNLEFT2:
       done= doRotate(90.0);              //angle is half of what it should be
       if(done) state = WANDER_FORWARD_1;
     break;

    case WANDER_FORWARD_2:
       done = goForwards(-10.0); 
       if(done) state = WANDER_TURNLEFT;
     break;

     case WANDER_TURNLEFT3:
       done= doRotate(45.0);              //angle is half of what it should be
       if(done) state = WANDER_FORWARD_1;
     break;
     
      case AVOID_BACK:
       done = goForwards(10.0);
       tone(digitalPin12, 5, 500) ;
       if(done) state = AVOID_ROTATE;
     break;

      case AVOID_ROTATE:
       done = doRotate(45.0); 
       if(done) state = WANDER_FORWARD_1;
     break;

     
      default:
      break;
  }
  //debug();
}

// --------------------------------------------------------

void debug() {
  // Only print out changes of state
  if(state != prevState) {
    prevState = state;
    if(state == WAITING)
      Serial.println("STATE_WAITING");
    if(state == WANDER_FORWARD_1)
      Serial.println("WANDER_FORWARD_1");
    if(state == WANDER_TURNLEFT)
      Serial.println("WANDER_TURNLEFT");      
    if(state == AVOID_BACK)
      Serial.println("AVOID_BACK");
    if(state == AVOID_TURNRIGHT) 
      Serial.println("AVOID_TURNRIGHT"); 
  }
  
}
// Following returns the distance to the object in cm
// Measurement initiated at 1 second (1000ms) time intervals
float getODist() {
  float dist;
  unsigned long currentMillis = millis();
  if(currentMillis - prevMillis > 1000) {
    prevMillis = currentMillis;
    digitalWrite(TxPin,LOW);
    delayMicroseconds(5);
    digitalWrite(TxPin,HIGH);
    delayMicroseconds(10);  
    digitalWrite(TxPin,LOW);   
    travelTime = pulseIn(RxPin,HIGH);
    dist = (float)travelTime*330.0/20000.0;
    return dist;
  } else return 1000;
}

