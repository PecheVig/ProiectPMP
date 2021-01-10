#include <NewPing.h> 
// Pinii motor 1
#define mpin00 6
#define mpin01 5
// Pinii motor 2
#define mpin10 3
#define mpin11 11
#define MAX_DISTANCE 250
//declararea unei variabile distance care este dolosita pentru a calcula distanta dintre un obiect aflat in fata masinutei si masinuta
int distance = 100;
//declararea unei variabile care va fi folosita pentru citirea caracterelor trimise prin bluetooth
char ch;
//definirea pinilor pentru senzorul ultrasonic
#define echo_pin A2
#define trig_pin A1

//definirea unei distante maxime pana la care sa caute sonarul
#define max_dist 200

//declararea unui obiect de tip NewPing pentru a lucra mult mai usor cu acesta
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
 
 Serial.begin(38400);
 delay(2000);
 distance = readPing();    //citirea distantei initiale
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
void loop()
{
  //verificam daca prin bluetooth se transmite ceva si daca da atunci punem acel ceva in variabila ch si afisam la serial monitor ce am citit
  if(Serial.available()){
  ch = Serial.read();
  Serial.println(ch);
  }
  //verificam pentru fiecare din inputul primit in ce caz suntem 
  if (ch=='F'){
    //Inainte
    distance=readPing();
    //verificam ca in fata masinutei sa nu se afle niciun obstacol, altfel daca se afla masinuta nu inainteaza
    if(distance>20){
  StartMotor (mpin00, mpin01, 1, 150);
  StartMotor (mpin10, mpin11, 1, 150);
  }
  }else if (ch=='G'){
    //Inapoi
    distance=readPing();
    
  StartMotor (mpin00, mpin01, 0, 150);
  StartMotor (mpin10, mpin11, 0, 150);
  }else if (ch=='L'){
    //Stanga
    distance=readPing();
    if(distance>20){
  StartMotor (mpin10, mpin11, 1, 128);
  }
  }else if (ch=='R'){
    //Dreapta
    distance=readPing();
    if(distance>20){
  StartMotor (mpin00, mpin01, 1, 128);
  }
  }else if (ch=='S'){
    //Stop
  StartMotor (mpin00, mpin01, 1, 0);
  StartMotor (mpin11, mpin10, 1, 0);
    delayStopped(500);
  }
 delay (500);
}

int readPing()      //functie pentru determinarea distantei
{
  delay(100);
  int cm = sonar.ping_cm();   //functia ping_cm returneaza o valoare incepand de la 1 pana la distanta maxima daca exista un obiect in radar sau 0 daca nu se afla nimic in fata masinutei
  if (cm==0)
  {
    cm=200; //daca nu se afla nimic in fata masinutei atunci setam varianila cm la valoarea maxima 
  }
  return cm;
}