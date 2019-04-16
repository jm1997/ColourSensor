// =====================================================
//
// Processing Script to Solve 1D Robot Grid Localisation
// ("Jess" Model)
//
// CBP 04-04-19
//
// =====================================================

//FALLING EDGE BOTH
final int STATE_0 = 0;

//RISING EDGE RED
//GOING FROM BLACK TO RED
//if((cc == COLOR_RED) && (ccPrev == COLOR_BACKG))
final int STATE_1 = 1;

//GOING FROM RED TO BLACK
//if((cc == COLOR_BACKG) && (ccPrev == COLOR_RED))
final int STATE_2 = 2;

//RISING EDGE GREEN
//GOING FROM BLACK TO GREEN
//if((cc == COLOR_GREEN) && (ccPrev == COLOR_BACKG)) 
final int STATE_3 = 3;

//GOING FROM GREEN TO BLACK
//if((cc == COLOR_BACKG) && (ccPrev == COLOR_GREEN))
final int STATE_4 = 4;

int state;

int COLOR_RED = 10;
int COLOR_GREEN = 11;
int COLOR_BACKG = 12;

color c;
color pixel;

int col, prevCol;
int change;
int count = 0;
int countRed = 0;
int countGreen = 0;

int cc, ccPrev;

int[] buffer = new int[10];
int index = 0;

PImage img;

void setup() {
  state = STATE_0;
  prevCol = COLOR_BACKG;
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
  ccPrev = COLOR_BACKG;
  
  // Fill the buffer with numbers not equal and not colors
  for(int i=0; i < buffer.length;i++) {
    buffer[i] = 100+i;
  }
  index = 1; // First place to write in buffer
}

void draw() {

  cc = getColor();

  printData(state,cc,ccPrev);
 
  // State machine detects rising and falling color edges and increases
  // count on falling edge
  switch(state) {
    case STATE_0:
  	if((cc == COLOR_RED) && (ccPrev == COLOR_BACKG)) {
      state = STATE_1;
      ccPrev = COLOR_RED;
    }
    if((cc == COLOR_GREEN) && (ccPrev == COLOR_BACKG)) {
      state = STATE_3;
      ccPrev = COLOR_GREEN;
    }
	  break;
	
	case STATE_1: //Rising edge RED
    if((cc == COLOR_BACKG) && (ccPrev == COLOR_RED)) {
      state = STATE_2;
    }
	break;
  
  case STATE_2: //Falling edge RED
    ccPrev = COLOR_BACKG;
     state = STATE_0;
     count++;
     buffer[index] = COLOR_RED;
     index++;
	break;

  case STATE_3: // Rising edge GREEN
    if((cc == COLOR_BACKG) && (ccPrev == COLOR_GREEN)) {
      state = STATE_4;
    }
  break;
  
  case STATE_4: // Falling edge GREEN
    ccPrev = COLOR_BACKG;
     state = STATE_0;
     count++;
     buffer[index] = COLOR_GREEN;
     index++;
  break;
  
  }
  // End of state machine
  
  // Scan the colored lines in the buffer and when adjacent are equal:
  // reduce the count by 2 and remove the two lines from the buffer.
  
  for(int i=1; i < index;i++) {
    if(buffer[i] == buffer[i - 1]) {
      count -=2;
      index -=2;
    }
  }
  
  delay(100);
	ccPrev = cc;

}

int colorChange(int col) {
  int result = 0;
  if(col != prevCol) {
    prevCol = col;
	if(col == color(255,0,0)) result = COLOR_RED;
	if(col == color(0,255,0)) result =  COLOR_GREEN;	
  } else {
    result = COLOR_BACKG;
  }
  return result;
  
}

int getColor() {
   pixel = (color)get(mouseX,mouseY);
   if(pixel == color(255,0,0))
   return COLOR_RED;
   else if(pixel == color(0,255,0))
   return COLOR_GREEN;
   else return COLOR_BACKG;
}

void printData(int state, int cc, int ccPrev) {
 print("state = "+state); 
 if(cc == COLOR_RED)print(" cc RED ");
 if(cc == COLOR_GREEN)print(" cc GREEN ");
 if(cc == COLOR_BACKG)print(" cc BACKG ");
 if(ccPrev == COLOR_RED)print(" ccPrev RED ");
 if(ccPrev == COLOR_GREEN)print(" ccPrev GREEN ");
 if(ccPrev == COLOR_BACKG)print(" ccPrev BACKG "); 
 print("CountRED = "+countRed);
 print(" CountGRN = "+countGreen);
 println(" Count = "+count);
}

void mouseClicked() {
  state = STATE_0;
  ccPrev = COLOR_BACKG;  
  countRed = 0;
  countGreen = 0;
  count = 0;
}
