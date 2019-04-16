// =====================================================
//
// Colour Sensing Robot for Dissertation Project
// (Jessica Mason - 16016599)
//
// =====================================================

#include <Wire.h>
#include "Adafruit_TCS34725.h"

//DEFINE STATES
#define STATE_0 0
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3

//DEFINE COLOURS
#define COLOUR_RED 10
#define COLOUR_GREEN 11
#define COLOUR_BLUE 12
#define COLOUR_YELLOW 13
#define COLOUR_BLACK 14

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

//GENERAL VARIABLES
//CURRENT STATE
int state;
//COUNT ON X AXIS
int countX;

//ARRAY
int pathX[10];
int index = 0;

//INITIALISE COLOUR SENSOR
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {

  //set state to state0 which is when the robot goes from a line onto the background
  state = STATE_0;
  countX = 0;
  prevColour = COLOUR_BLACK;
  
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
  
  //FININTE STATE MACHINE
  switch(state){

    case STATE_0:
      //GOES ONTO A RED LINE
      if((currentColour == COLOUR_RED) && (prevColour == COLOUR_BLACK)){
        state = STATE_1;
        prevColour = COLOUR_RED;
      }
      //GOES ONTO A GREEN LINE
      if((currentColour == COLOUR_GREEN) && (prevColour == COLOUR_BLACK)){
        state = STATE_2;
        prevColour = COLOUR_GREEN;
      }

    //RED BEHAVIOUR
    case STATE_1:
      //GOING OVER A RED LINE 
      if(currentColour == COLOUR_RED){
        prevColour = COLOUR_RED;
        state = STATE_3;
      }
      
    break;
    
    //GREEN BEHAVIOUR
    case STATE_2:
      //GOING OVER A GREEN LINE 
      if(currentColour == COLOUR_GREEN){
        prevColour = COLOUR_GREEN;
        //STATE 3 = FALLING EDGE NEW LINE
        state = STATE_3;
      }

    break;
      
    //FALLING EDGE NEW LINE
    case STATE_3:
    //COMING OFF A RED LINE
    if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_RED)){
      countX++;
      pathX[index] = COLOUR_RED;
      index++;
      prevColour = COLOUR_BLACK;
      state = STATE_0;
    }
    //COMING OFF A GREEN LINE
    if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_GREEN)){
      countX++;
      pathX[index] = COLOUR_GREEN;
      index++;
      prevColour = COLOUR_BLACK;
      state = STATE_0;
    }
          
    break;
   
  } //END OF FINITE STATE MACHINE

  //FOR WHEN IT GOES BACK ON ITSELF
  for(int i=1; i < index;i++) {
    //if newest item in the array is the same as the last
    if(pathX[i] == pathX[i - 1]) {
      countX -=2;
      index -=2;
    }
  }

  //PRINTING FOR DEBUGGING PURPOSES
  Serial.print("hDegrees: ");
  Serial.print(hDegrees);
  Serial.println("");
  Serial.print("state: ");
  Serial.print(state);
  Serial.println("");
  Serial.print("CountX: ");
  Serial.print(countX);
  Serial.println("");
  Serial.println("");
  
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
    
    if((hDegrees >= 0) && (hDegrees < 25)){
      outputColour = COLOUR_RED;
      Serial.print("outputColour: RED");
      Serial.println("");
    } else
    if((hDegrees >= 25) && (hDegrees < 35)){
      outputColour = COLOUR_BLACK;
      Serial.print("outputColour: BLACK");
      Serial.println("");
    } else
    if((hDegrees >= 65) && (hDegrees < 130)){
      outputColour = COLOUR_GREEN;
      Serial.print("outputColour: GREEN");
      Serial.println("");
    } else
    if((hDegrees >= 130) && (hDegrees < 260)){
      outputColour = COLOUR_BLUE;
      Serial.print("outputColour: BLUE");
      Serial.println("");
    } else
    if((hDegrees >= 35) && (hDegrees < 65)){
      outputColour = COLOUR_YELLOW;
      Serial.print("outputColour: YELLOW");
      Serial.println("");
    }
      

    return outputColour;
      
  } //END OF getColour()
