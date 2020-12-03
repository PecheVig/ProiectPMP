#define mpin00 8
#define mpin01 9

#define mpin10 10
#define mpin11 11
char ch;
char ch1;
void setup()
{
 digitalWrite(mpin00, 0);
 digitalWrite(mpin01, 0);
 digitalWrite(mpin10, 0);
 digitalWrite(mpin11, 0);
 pinMode (mpin00, OUTPUT);
 pinMode (mpin01, OUTPUT);
 pinMode (mpin10, OUTPUT);
 pinMode (mpin11, OUTPUT);
 Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void StartMotor (int m1, int m2, int forward, int speed)
{

 if (speed==0) // oprire
 {
 digitalWrite(m1, 0);
 digitalWrite(m2, 0);
 }
 else
 {
 if (forward)
 {
 digitalWrite(m2, 0);
   
   analogWrite(m1, speed); // folosire PWM
 }
 else
 {
 digitalWrite(m1, 0);
 analogWrite(m2, speed);
 }
 }
}
void delayStopped(int ms)
{
 StartMotor (mpin00, mpin01, 0, 0);
 StartMotor (mpin10, mpin11, 0, 0);
 delay(ms);
}
void serialEvent() {
  ch=(char)Serial.read();
}
void loop()
{
  if (ch=='W'||ch=='w'){
    //Inainte
    if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin00, mpin01, 1, 128);
  StartMotor (mpin10, mpin11, 1, 128);
 
  }
  if (ch=='s'||ch=='S'){
    //Inapoi
  StartMotor (mpin01, mpin00, 1, 128);
  StartMotor (mpin11, mpin10, 1, 128);
    ch='\n';
  }
  if (ch=='a'||ch=='A'){
    //Stanga
     if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin01, mpin00, 1, 128);
  StartMotor (mpin10, mpin11, 1, 128);
  }
  if (ch=='d'||ch=='D'){
    //Dreapta
    if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin00, mpin01, 1, 128);
  StartMotor (mpin11, mpin10, 1, 128);
    ch='\n';
  }
  if (ch=='k'||ch=='K'){
    //Stop
  StartMotor (mpin00, mpin01, 1, 0);
  StartMotor (mpin11, mpin10, 1, 0);
    ch='\n';
    delayStopped(500);
  }
 delay (500);
}
