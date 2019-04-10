// =====================================================
//
// Colour Sensing Robot for Dissertation Project
// (Jessica Mason - 16016599)
//
// =====================================================

#include <Wire.h>
#include "Adafruit_TCS34725.h"

//DEFINE COLOURS
#define BLACK 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
//DEFINE STATES
#define state0 5
#define state1 6
#define state2 7
#define state3 8
#define state4 9

//NORMALISED RGB VALUES
double rNorm;
double gNorm;
double bNorm;
//HUE
double h;
double hDegrees;
//DEBUG
double g; 
//EQUATION SECTIONS
double topA;
double bottomA;
double bottomB;
//PI values (pretty sure these are built in, check that)
double Pi = 3.1415926535897932384626433832795;
double twoPi = 6.283185307179586476925286766559;

//COLOUR SENSING VARIABLES
int currentColour;
int prevColour;
int outputColour;

int state;
int count;

int state;C:\Users\Jess\Documents\GitHub\ColourSensor\Simulations
bool stateRunning;

//INITIALISE COLOUR SENSOR
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  
  colourChange = false;
  stateRunning = false;

  //set state to state0 which is when the robot goes from a line onto the background
  state = state0;
  count = 0;
  prevColour = BLACK;
  
  Serial.begin(9600);

  //CHECK COLOUR SENSOR IS CONNECTED
  if (tcs.begin()) {
    Serial.println("Found sensor");
    Serial.println(" ");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    Serial.println(" ");
    while (1);
  }
 
}// END OF setup()

void loop(void) {
 

  //this runs the get colour function and recieves the outputted colour
  currentColour = getColour();
  Serial.print("currentColour: ");
  Serial.print(currentColour);
  Serial.println("");
  Serial.print("prevColour: ");
  Serial.print(prevColour);
  Serial.println("");
  Serial.print("state: ");
  Serial.print(state);
  Serial.println("");

  //FININTE STATE MACHINE
  switch(state){
    
  } //END OF FINITE STATE MACHINE
  
} //END OF MAIN LOOP

int getColour(){
    
  uint16_t r, g, b, c, colorTemp, lux;
  
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
  //NORMALISE VALUES
  rNorm = (double)r/double(r + g + b);
  gNorm = (double)g/double(r + g + b);
  bNorm = (double)b/double(r + g + b);

  //CALCULATE EQUATION SECTIONS
  topA = 2 * rNorm - gNorm - bNorm;
  bottomA = sqrt(2.0 / 3.0);
  bottomB = sqrt(6 * (rNorm * rNorm + gNorm * gNorm + bNorm * bNorm - rNorm * gNorm - gNorm * bNorm - bNorm * rNorm));
  
  //CALCULATE H IN RADIANS
  if (bNorm <= gNorm) {
    h = acos(( topA / (bottomA * bottomB)));
    //CONVERT H TO DEGREES
    hDegrees = h * 180 / Pi;
  }
  if (bNorm > gNorm) {
    g = acos(( topA / (bottomA * bottomB)));
    h = twoPi - acos(( topA / (bottomA * bottomB)));
    //CONVERT H TO DEGREES
    hDegrees = h * 180 / Pi;
  }
    
    if((hDegrees >= 0) && (hDegrees < 30)){
      outputColour = RED;
    } else
    if((hDegrees >= 30) && (hDegrees < 65)){
      outputColour = YELLOW;
    } else
    if((hDegrees >= 65) && (hDegrees < 130)){
      outputColour = GREEN;
    } else
    if((hDegrees >= 130) && (hDegrees < 260)){
      outputColour = BLUE;
    } else
      outputColour = BLACK;

    return outputColour;
      
  } //END OF getColour()
