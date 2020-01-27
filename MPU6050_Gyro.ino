/**
Circuit
    MPU6050    Arduino
    Vcc        5V
    GND        GND
    SCL        A5(SCL in Arduino) 
    SDA        A4(SDA in Arduino)
    XDA        -
    XCL        -
    AD0        GND or Vcc (to make LSB 0 or 1 in data bus -for use two PMUs)
    INT        -
*/

#include <Wire.h>

long accelX,accelY,accelZ;
float gForceX,gForceY,gForceZ;

long gyroX,gyroY,gyroZ;
float rotX,rotY,rotZ;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setUpMPU();
}
void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  //printData();
  printDataForArduino();
  delay(100);
}
void setUpMPU(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission();

}
void recordAccelRegisters(){

  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);

  while(Wire.available()<6);
  accelX=Wire.read()<<8|Wire.read();
  accelY=Wire.read()<<8|Wire.read();
  accelZ=Wire.read()<<8|Wire.read();  
  processAccelData();

}

void processAccelData(){
  gForceX=accelX / 16384.0;
  gForceY=accelY / 16384.0;
  gForceZ=accelZ / 16384.0;
}

void recordGyroRegisters(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);

  while(Wire.available()<6);
  gyroX=Wire.read()<<8|Wire.read();
  gyroY=Wire.read()<<8|Wire.read();
  gyroZ=Wire.read()<<8|Wire.read();  
  processGyroData();


}

void processGyroData(){
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}


void printData(){
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print("\t Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.print(gForceZ);
  Serial.println();

}
void printDataForArduino(){
  Serial.print(rotX);
  Serial.print(",");
  Serial.print(rotY);
  Serial.print(",");
  Serial.print(rotZ);
  Serial.print(",");
  Serial.print(gForceX);
  Serial.print(",");
  Serial.print(gForceY);
  Serial.print(",");
  Serial.print(gForceZ);
  Serial.print(",");
  Serial.println();
}









