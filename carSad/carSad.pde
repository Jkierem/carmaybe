import processing.serial.*;

Serial myPort;  // Create object from Serial class

boolean W = false;
boolean S = false;
boolean D = false;
boolean A = false;

int units = 0;
int decs = 0;
int NONE = 0;

void setup()
{
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  printArray(Serial.list());
  myPort = new Serial(this, "/dev/ttyACM0", 9600);
}

void send(int s){
  myPort.write(s);
}

void draw(){
  if( W || S || A || D ){
    if( A ){
      units = 2;
    } else if( D ){
      units = 1;
    } else {
      units = 0;
    }
    
    if( W ){
      decs = 2;
    }else if( S ){
      decs = 1;
    }else {
      decs = 0;
    }
    send((decs * 10) + units);
  }else{
    send(NONE);
  }
}

void keyPressed(){
  if( key == 'w' || key == 'W' ){
    W = true;
  }
  if( key == 'd' || key == 'D' ){
    D = true;
  }
  if( key == 's' || key == 'S' ){
    S = true;
  }
  if( key == 'a' || key == 'A' ){
    A = true;
  }
}

void keyReleased(){
  if( key == 'w' || key == 'W' ){
    W = false;
  }
  if( key == 'd' || key == 'D' ){
    D = false;
  }
  if( key == 's' || key == 'S' ){
    S = false;
  }
  if( key == 'a' || key == 'A' ){
    A = false;
  }
}
