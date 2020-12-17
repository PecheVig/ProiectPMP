#define mpin00 8
#define mpin01 9

#define mpin10 10
#define mpin11 11


#define echo_pin 2
#define trig_pin 3 
long duration; 
int distance;


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

 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 
 Serial.begin(9600);
  pinMode(13, OUTPUT);
}
void senzor(){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 0.034 / 2;
  
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
//aici ar trebuii sa schimb ca ch sa nu vina de la serial input ci de la modulul bluetooth master
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
  if ((ch=='W'||ch=='w')&&distance>20){
    //Inainte
    if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin00, mpin01, 1, 128);
  StartMotor (mpin10, mpin11, 1, 128);
 
  }
  if ((ch=='s'||ch=='S')&&distance>20){
    //Inapoi
  StartMotor (mpin01, mpin00, 1, 128);
  StartMotor (mpin11, mpin10, 1, 128);
    ch='\n';
  }
  if ((ch=='a'||ch=='A')&&distance>20){
    //Stanga
     if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin01, mpin00, 1, 128);
  StartMotor (mpin10, mpin11, 1, 128);
  }
  if ((ch=='d'||ch=='D')&&distance>20){
    //Dreapta
    if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin00, mpin01, 1, 128);
  StartMotor (mpin11, mpin10, 1, 128);
    ch='\n';
  }
  if (ch=='k'||ch=='K'||distance<=20){
    //Stop
  StartMotor (mpin00, mpin01, 1, 0);
  StartMotor (mpin11, mpin10, 1, 0);
    ch='\n';
    delayStopped(500);
  }
 delay (500);
}