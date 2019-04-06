// =====================================================
//
// Processing Script to Solve 1D Robot Grid Localisation
// ("Jess" Model)
//
// CBP 04-04-19
//
// =====================================================

//ON THE BACKGROUND
final int STATE_0 = 0;
//
final int STATE_1 = 1;
//
final int STATE_2 = 2;
final int STATE_3 = 3;
final int STATE_4 = 4;
int state;

int COLOR_RED = 10;
int COLOR_GREEN = 11;
int COLOR_BACKG = 12;

int cc, ccPrev;

PImage img;

void setup() {
  state = STATE_0;

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
  

}

void draw() {

  cc = getColor();

  //PUT STATES HERE
  
  delay(100);
	//ccPrev = cc;
 

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
