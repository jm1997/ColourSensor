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
final int STATE_5 = 5;
final int STATE_6 = 6;

//DECLARE COLOURS
int COLOUR_RED = 10;
int COLOUR_GREEN = 11;
int COLOUR_BLUE = 12;
int COLOUR_YELLOW = 13;
int COLOUR_BLACK = 14;

int state;
int countX;
int lastLine;
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
  countX = 0;
  //SET LAST LINE
  lastLine = COLOUR_BLACK;
  
} //END OF SETUP

void draw() {

  //CURRENT COLOUR IS OUTPUT FROM GETCOLOUR FUNCTION
  currentColour = getColour();
  //PRINT FOR DEBUGGING REASONS
  printData(state,currentColour,prevColour);

  //STATE MACHINE
  switch(state) {
         
    //BACKGROUND BEHAVIOUR
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
    
    break;
     
    //RED BEHAVIOUR
    case STATE_1:
      //GOING OVER THE FIRST RED LINE
      if((currentColour == COLOUR_RED) && (lastLine == COLOUR_BLACK)){
        prevColour = COLOUR_RED;
        state = STATE_3;
      }
      //GOING OVER A NEW RED LINE (NOT GOING BACK ON ITSSELF)
      if((currentColour == COLOUR_RED) && (lastLine == COLOUR_GREEN)){
        prevColour = COLOUR_RED;
        state = STATE_3;
      }
      //GOING BACK OVER THE SAME RED LINE (GOING BACK ON ITSELF)
      if((currentColour == COLOUR_RED) && (lastLine == COLOUR_RED)){
        prevColour = COLOUR_RED;
        //STATE 4 = FALLING EDGE SAME LINE AGAIN (GOING BACK ON ITSELF)
        state = STATE_4;
      }
      
    break;
    
    //GREEN BEHAVIOUR
    case STATE_2:
    //GOING OVER THE FIRST GREEN LINE
    if((currentColour == COLOUR_GREEN) && (lastLine == COLOUR_BLACK)){
      prevColour = COLOUR_GREEN;
      //STATE 3 = FALLING EDGE NEW LINE
      state = STATE_3;
    }
    //GOING OVER A NEW GREEN LINE (NOT GOING BACK ON ITSELF)
    if((currentColour == COLOUR_GREEN) && (lastLine == COLOUR_RED)){
      prevColour = COLOUR_GREEN;
      //STATE 3 = FALLING EDGE NEW LINE
      state = STATE_3;
    }
    //GOING BACK OVER THE SAME GREEN LINE
    if((currentColour == COLOUR_GREEN) && (lastLine == COLOUR_GREEN)){
       prevColour = COLOUR_GREEN;
       //STATE 4 = FALLING EDGE SAME LINE AGAIN (GOING BACK ON ITSELF)
       state = STATE_4;
    }
    
    break;
      
    //FALLING EDGE NEW LINE
    case STATE_3:
    if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_RED)){
      countX++;
      lastLine = COLOUR_RED;
      prevColour = COLOUR_BLACK;
      state = STATE_0;
    }
    if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_GREEN)){
      countX++;
      lastLine = COLOUR_GREEN;
      prevColour = COLOUR_BLACK;
      state = STATE_0;
    }
      
    break;
    
    //FALLING EDGE SAME LINE AGAIN (GOING BACK ON ITSELF
    case STATE_4:
    if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_RED)){
      countX--;
      lastLine = COLOUR_RED;
      state = STATE_0;
    }
    if((currentColour == COLOUR_BLACK) && (prevColour == COLOUR_GREEN)){
      countX--;
      lastLine = COLOUR_RED;
      state = STATE_0;
    }
    
    break;
      
  }//END OF switch(state)
  
  delay(100);
  //SET PREVIOUSLY READ COLOUR TO prevColour
	//prevColour = currentColour;

} //END OF draw

//IGNORE EVERYTHING BELOW HERE

int getColour() {
   pixel = (color)get(mouseX,mouseY);
   if(pixel == color(255,0,0))
   return COLOUR_RED;
   else if(pixel == color(0,255,0))
   return COLOUR_GREEN;
   else return COLOUR_BLACK;
} //END OF getColour

void printData(int state, int currentColour, int prevColour) {
 print("state = "+state); 
 if(currentColour == COLOUR_RED)print(" currentColour RED ");
 if(currentColour == COLOUR_GREEN)print(" currentColour GREEN ");
 if(currentColour == COLOUR_BLACK)print(" currentColour BLACK ");
 if(prevColour == COLOUR_RED)print(" prevColour RED ");
 if(prevColour == COLOUR_GREEN)print(" prevColour GREEN ");
 if(prevColour == COLOUR_BLACK)print(" prevColour BLACK "); 
 if(lastLine == COLOUR_RED)print(" lastLine RED ");
 if(lastLine == COLOUR_GREEN)print(" lastLine GREEN ");
 if(lastLine == COLOUR_BLACK)print(" lastLine BLACK ");
 println(" Count X = "+countX);
} //END OF printData

void mouseClicked() {
  //RESET EVERYTHING
  state = STATE_0;
  prevColour = COLOUR_BLACK;  
  countX = 0;
} //END OF mouseClicked
