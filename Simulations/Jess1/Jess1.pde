// =====================================================
//
// Processing Script to Solve 1D Robot Grid Localisation
// ("Jess" Model)
//
// CBP 04-04-19
//
// =====================================================

//DECLARE STATES
final int STATE_0 = 0;
final int STATE_1 = 1;
final int STATE_2 = 2;
final int STATE_3 = 3;
final int STATE_4 = 4;

//DECLARE COLOURS
int COLOUR_RED = 10;
int COLOUR_GREEN = 11;
int COLOUR_BLUE = 12;
int COLOUR_YELLOW = 13;
int COLOUR_BLACK = 14;


int state;
int count;
//CURRENT COLOUR
int currentColour;
//LAST COLOUR
int prevColour;

PImage img;
color c;
color pixel;

void setup() {

  size(500,500);
  noStroke();
  
  fill(255,0,0);
  rect(100,100,25,300); 
  fill(0,255,0);
  rect(150,100,25,300);  
  fill(255,0,0);
  rect(200,100,25,300); 
  fill(0,255,0);
  rect(250,100,25,300);  
  fill(255,0,0);
  rect(300,100,25,300); 
  fill(0,255,0);
  rect(350,100,25,300);    
  
  img = get();
  println("hi");
  
  //SET PREV COLOUR TO BACKGROUND
  prevColour = COLOUR_BLACK;  
  //SET STATE TO STARTING STATE OF BEING ON THE BACKGROUND (GOING FROM LINE TO BACKGROUND)
  state = STATE_0;
  //SET COUNT TO 0 TO START WITH
  count = 0;
  
} //END OF SETUP

void draw() {

  //CURRENT COLOUR IS OUTPUT FROM GETCOLOUR FUNCTION
  currentColour = getColour();
  printData(state,currentColour,prevColour);

  //PUT STATES HERE
  switch(state){
    case STATE_0:
      if((currentColour == COLOUR_RED) && (prevColour == COLOUR_BLACK)){
        state = STATE_1;
        prevColour = COLOUR_RED;
      }
      if((currentColour == COLOUR_GREEN) && (prevColour == COLOUR_BLACK)){
         state = STATE_3;
         prevColour = COLOUR_GREEN;
      }
      
    break;
     
    case STATE_1:
      if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_RED)){
         state = STATE_2;
      }
      
    break;
    
    case STATE_2:
       prevColour = COLOUR_BLACK;
       state = STATE_0;
       count++;
    
    break;
      
    case STATE_3:
      if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_GREEN)){
        state = STATE_4;
      }
    
    break;
    
    case STATE_4:
      prevColour = COLOUR_BLACK;
      state = STATE_0;
      count++;
    
    break;
      
  }//END OF switch(state)
  
  delay(100);
  //SET PREVIOUSLY READ COLOUR TO prevColour
	prevColour = currentColour;

}

//IGNORE EVERYTHING BELOW HERE

int getColour() {
   pixel = (color)get(mouseX,mouseY);
   if(pixel == color(255,0,0))
   return COLOUR_RED;
   else if(pixel == color(0,255,0))
   return COLOUR_GREEN;
   else return COLOUR_BLACK;
}

void printData(int state, int currentColour, int prevColour) {
 print("state = "+state); 
 if(currentColour == COLOUR_RED)print(" currentColour RED ");
 if(currentColour == COLOUR_GREEN)print(" currentColour GREEN ");
 if(currentColour == COLOUR_BLACK)print(" currentColour BLACK ");
 if(prevColour == COLOUR_RED)print(" prevColour RED ");
 if(prevColour == COLOUR_GREEN)print(" prevColour GREEN ");
 if(prevColour == COLOUR_BLACK)print(" prevColour BLACK "); 
 //print("CountRED = "+countRed);
 //print(" CountGRN = "+countGreen);
 println(" Count = "+count);
}

void mouseClicked() {
  //RESET EVERYTHING
  state = STATE_0;
  prevColour = COLOUR_BLACK;  
  //countRed = 0;
  //countGreen = 0;
  count = 0;
}
