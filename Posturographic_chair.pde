import processing.serial.*;
Serial myPort; 
int x, y, a, b;   
PFont f;
String portName, message;

void setup()
{
  size(500, 500);
  stroke(255); 
   portName = Serial.list()[0]; 
  myPort = new Serial(this, portName, 9600);
 
  f = createFont("Arial", 16, true); 
  textFont(f, 16); 
}

void draw(){
  fill(0);
  clear();
  stroke(255); // na biało linia
  line(250, 0, 250, 500); // kreska pionowa
  line(0, 250, 500, 250); // kreska pozioma
  fill(255); // ustaw kolor wypełnienia na biały
  stroke(255,0,0); // na czerwono linia
  line(205,260,295,260); // kwadrat gorna pozioma
  line(295,260,295,350); // kwadrat prawa pionowa
  line(295,350,205,350); // kwadrat dolna pozioma
  line(205,350,205,260); // kwadrat lewa pionowa

  ellipse(x/2, 500-(y/2), 25, 25);
  text("X="+(x)+" Y="+(y)+"\n\n"+message,10,20);
}

void serialEvent(Serial port){ 
  String input = port.readStringUntil(10);
  if (input != null){
    if(input.length() < 10){
   
    int[] vals = int(splitTokens(input, "\t"));
    
    
    a = vals[0]; 
    b = vals[1];
   
    x = b*10 ;
    y = a*10;
    }
    else{message = input;
   }
  }
}
