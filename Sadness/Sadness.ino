const int snsAPin = 0;    // define pin for detecting current of motor A
const int snsBPin = 1;    // define pin for detecting current of motor B
const int dirAPin = 7;    // define pin used to control rotational direction of motor A
const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;    // define pin used to control rotational direction of motor B
const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B

const bool BACKWARDS = true;
const bool FORWARDS = false;
const int FULL = 255;
const int HALF = 128;

const int WKey = 119;
const int AKey = 97;
const int SKey = 115;
const int DKey = 100;
const int EKey = 101;
const int QKey = 113;
const int SpaceKey = 32;
const int NONE = 256;

const int Forwards = 20;
const int Backwards = 10;
const int ForRight = 22;
const int ForLeft = 21;
const int BackRight = 12;
const int BackLeft = 11;

int in = 0;

class Motor {
  protected:
    const int pwmPin;
    const int dirPin;
  public:
    Motor(int pwm, int dir): pwmPin(pwm), dirPin(dir){}
    
    void goForwards(byte motorSpeed){
        digitalWrite(this->dirPin, FORWARDS);
        analogWrite(this->pwmPin, motorSpeed);
    }

    void goBackwards(byte motorSpeed){
        digitalWrite(this->dirPin, BACKWARDS);
        analogWrite(this->pwmPin, motorSpeed);
    }

    void brake(){
        this->goForwards(0);
    }
};

class Car {
  protected:
    Motor right;
    Motor left;
    int mode;
  public:
    Car(Motor r,Motor l): right(r), left(l){ this->mode = NONE; }

    void goForwards(){
      this->left.goForwards(255);
      this->right.goForwards(255);  
    }

    void goBackwards(){
      this->left.goBackwards(255);
      this->right.goBackwards(255);
    }

    void rotateCounterClockwise(){
      this->right.goForwards(255);
      this->left.goBackwards(255);
    }

    void rotateClockwise(){
      this->left.goForwards(255);
      this->right.goBackwards(255);
    }

    void brake(){
      this->left.brake();
      this->right.brake();
    }

    void changeMode(int mode){
      this->mode = mode;
    }

    void control(byte left, byte right, bool dir){
      if( dir == FORWARDS ){
        this->left.goForwards(left);
        this->right.goForwards(right);
      } else {
        this->left.goBackwards(left);
        this->right.goBackwards(right);
      }
    }

    void execute(){
      switch(this->mode){
        case Forwards:
          this->goForwards();
          break;
        case Backwards:
          this->goBackwards();
          break;
        case ForLeft:
          this->control(HALF,FULL,FORWARDS);
          break;
        case ForRight:
          this->control(FULL,HALF,FORWARDS);
          break;
        case BackLeft:
          this->control(HALF,FULL,BACKWARDS);
          break;
        case BackRight:
          this->control(FULL,HALF,BACKWARDS);
          break;
        default:
          this->brake();
          break;
      }
    }
};

Motor motorA(pwmAPin,dirAPin);
Motor motorB(pwmBPin,dirBPin);
Car car(motorA,motorB);

int readByte(bool debug=true){
  if (Serial.available() > 0) {
    int in = Serial.read();
    if( debug ){
      Serial.println(in,DEC);
    }
    return in;
  }
  return NONE;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
  pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
  pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
  pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode
  Serial.begin(9600);
}

void loop() {
   int in = readByte(true);
   car.changeMode(in);
   car.execute();
   delay(600);
}
