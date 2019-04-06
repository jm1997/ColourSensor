#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define UNDEFINED 0

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
int lastLine;
bool colourChange;
int count;

//INITIALISE COLOUR SENSOR
/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  
  colourChange = false;
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
  
  int colour;

  colour = getColour();

  //ON THE BACKGROUND
  if (colour == UNDEFINED){
    colourChange = false;
  }
  //COLOUR HAS CHANGED
  if (colour != prevColour){
    colourChange = true;
  }
  //NEW LINE DETECTED
  if ((colourChange = true) && (colour != lastLine)){
    count ++;
    lastLine = colour;
    colourChange = false;
  }
  //GOING BACK OVER THE SAME LINE
  if ((colourChange = true) && (colour = lastLine)){
    count --;
    colourChange = false;
  }

  prevColour = colour;
  
  Serial.print("count: ");
  Serial.print(count);
  Serial.println(" ");
  Serial.print("colour: ");
  Serial.print(colour); 
  Serial.println(" ");
  Serial.print("prevColour: ");
  Serial.print(prevColour);   
  Serial.println(" ");
  Serial.print("lastLine: ");
  Serial.print(lastLine); 
  Serial.println(" ");
       
} //END OF loop()

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

    //PRINTING FOR DEBUGGING PURPOSES
    Serial.print("h:(degrees) ");
    Serial.print(hDegrees);
    Serial.println(" ");
    Serial.println(" ");
    
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
      outputColour = UNDEFINED;

    return outputColour;
      
  } //END OF getColour()
