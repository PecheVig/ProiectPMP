#define xInp A1
#define yInp A2
#define zInp A3

int RawMin = 0;
int RawMax = 1023;

const int sampleSize = 10;

void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);

  
}

void loop() {
  
  int x=ReadAxis(xInp);
  int y=ReadAxis(yInp);
  int z=ReadAxis(zInp);


  long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000);
  long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000);
  long zScaled = map(zRaw, RawMin, RawMax, -3000, 3000);

  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;
  //cazuri pentru fiecare directie in parte....stanga, dreapta, inainte, inapoi
  if(xAccel==-1&&yAccel==-0&&zAccel==-0){
    //transmit semnalul de inapoi spre modulul bluetooth slave
  }
  if(xAccel==-0&&yAccel==-1&&zAccel==-0){
    //transmit semnalul de dreapta spre modulul bluetooth slave
  }
  if(xAccel==-0&&yAccel==1&&zAccel==-0){
    //transmit semnalul de stanga spre modulul bluetooth slave
  }
  if(xAccel==1&&yAccel==-0&&zAccel==-0){
    //transmit semnalul de inainte spre modulul bluetooth slave
  }
  
}
