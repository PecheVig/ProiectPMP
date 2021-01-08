#include <Wire.h>
#include <NewPing.h> 
// Pinii motor 1
#define mpin00 6
#define mpin01 5
// Pinii motor 2
#define mpin10 3
#define mpin11 11
#define MAX_DISTANCE 250

int distance = 100;

char ch;
char ch1;

#define echo_pin A2
#define trig_pin A1
#define max_dist 200

NewPing sonar(trig_pin, echo_pin, max_dist);
void setup() {
 // configurarea pinilor motor ca iesire, initial valoare 0
 digitalWrite(mpin00, 0);
 digitalWrite(mpin01, 0);
 digitalWrite(mpin10, 0);
 digitalWrite(mpin11, 0);
 pinMode (mpin00, OUTPUT);
 pinMode (mpin01, OUTPUT);
 pinMode (mpin10, OUTPUT);
 pinMode (mpin11, OUTPUT);
 
 Serial.begin(9600);
 // pin LED
 pinMode(13, OUTPUT);
 delay(2000);
 distance = readPing();    // Get Ping Distance.
 delay(100);
 
}
void senzor(){
  int distance = readPing();
  delay(100);
}
// Funcție pentru controlul unui motor
// Intrare: pinii m1 și m2, direcția și viteza
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
// Funcție de siguranță
// Execută oprire motoare, urmată de delay
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
  distance=readPing();
  Serial.println(distance);
  
  if ((ch=='W'||ch=='w')&&distance>20){
    //Inainte
    Serial.println(ch);
    if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin00, mpin01, 1, 128);
  StartMotor (mpin10, mpin11, 1, 128);
 
  }else if ((ch=='s'||ch=='S')&&distance>20){
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
  }else if ((ch=='d'||ch=='D')&&distance>20){
    //Dreapta
    if (ch!=ch1){
    delayStopped(500);
      ch1=ch;
    }
  StartMotor (mpin00, mpin01, 1, 128);
  StartMotor (mpin11, mpin10, 1, 128);
    ch='\n';
  }else if (ch=='k'||ch=='K'||distance<=20){
    //Stop
  StartMotor (mpin00, mpin01, 1, 0);
  StartMotor (mpin11, mpin10, 1, 0);
    ch='\n';
    delayStopped(500);
  }
 delay (500);
}

int readPing()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(100);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}