// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include "Wire.h" // This library allows you to communicate with I2C devices.
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 6, true); // request a total of 3*2=6 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  //citim valorile pentru componentele x, y si z ale accelerometrului.
  accelerometer_x = ( Wire.read()| Wire.read() << 8);
  accelerometer_x = accelerometer_x/256;
  accelerometer_y = ( Wire.read()| Wire.read() << 8); 
  accelerometer_y=accelerometer_y/256;
  accelerometer_z = ( Wire.read()| Wire.read() << 8); 
  accelerometer_z=accelerometer_z/256;
  //verificam pe care pozitie suntem
  if(accelerometer_x<1000&&accelerometer_y<-8000){
  //stanga
  Serial.println('L');
  }
  if(accelerometer_x<1000&&accelerometer_y>8000){
  //drapta
  Serial.println('R');
  }
  if(accelerometer_x>8000&&accelerometer_y<1000){
  //drapta
  Serial.println('G'); 
  }
  if(accelerometer_x<-8000&&accelerometer_y<1000){
    //stanga
    Serial.println('F');
  }
  delay(1000);
}