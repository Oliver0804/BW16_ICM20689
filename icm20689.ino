#include <Wire.h>

#define ADDRESS      0x68 // AD0 = 0 : 0x68, AD0 = 1 : 0x69

#define GYRO_CONFIG             0x1B
#define ACCEL_CONFIG            0x1C

#define ACCEL_XOUT_H            0x3B
#define ACCEL_YOUT_H            0x3D
#define ACCEL_ZOUT_H            0x3F
#define GYRO_XOUT_H             0x43
#define GYRO_YOUT_H             0x45
#define GYRO_ZOUT_H             0x47

#define PWR_MGMT_1              0x6B
#define PWR_MGMT_2              0x6C

byte rawAX[2], rawAY[2], rawAZ[2];
byte rawGX[2], rawGY[2], rawGZ[2];
float rawACCX, rawACCY, rawACCZ;
float rawGYROX, rawGYROY, rawGYROZ;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Connecting to ICM-20689...");
  
  // Power Management 1 setup
  Wire.beginTransmission(ADDRESS);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x01);
  Wire.endTransmission();

  // Power Management 2 setup
  Wire.beginTransmission(ADDRESS);
  Wire.write(PWR_MGMT_2);
  Wire.write(0x00);         
  Wire.endTransmission();

  // Accelerometer Configuration
  Wire.beginTransmission(ADDRESS);
  Wire.write(ACCEL_CONFIG);
  Wire.write(0x00);         
  Wire.endTransmission();

  // Gyroscope Configuration
  Wire.beginTransmission(ADDRESS);
  Wire.write(GYRO_CONFIG);
  Wire.write(0x00);         
  Wire.endTransmission();
  
  Serial.println("  Acc_X           Acc_Y             Acc_Z                  Gyro_X           Gyro_Y           Gyro_Z");
}
void loop() {
  getACC();
  Serial.print(rawACCX/16384, DEC); Serial.print('\t');
  Serial.print(rawACCY/16384, DEC); Serial.print('\t');
  Serial.print(rawACCZ/16384, DEC); Serial.print("\t\t");

  getGYRO();
  Serial.print(rawGYROX/131, DEC); Serial.print('\t');
  Serial.print(rawGYROY/131, DEC); Serial.print('\t');
  Serial.print(rawGYROZ/131, DEC);

 
  Serial.println();
  delay(20);
}
void getACC(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS,2,1);  
  for(int i = 0; i<2 ; i++)
  {
    rawAX[i] = Wire.read();
  }
  rawACCX = rawAX[1] | rawAX[0]<<8;

  //==================================================
  Wire.beginTransmission(ADDRESS);
  Wire.write(ACCEL_YOUT_H);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS,2,1);
  for(int i = 0; i<2 ; i++)
  {
    rawAY[i] = Wire.read();
  }
  rawACCY = rawAY[1] | rawAY[0]<<8;
  

  //==================================================
  Wire.beginTransmission(ADDRESS);
  Wire.write(ACCEL_ZOUT_H);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS,2,1);
  for(int i = 0; i<2 ; i++)
  {
    rawAZ[i] = Wire.read();
  }
  rawACCZ = rawAZ[1] | rawAZ[0]<<8;
}


void getGYRO(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS,2,1);
  for(int i = 0; i<2 ; i++)
  {
    rawGX[i] = Wire.read();
  }
  rawGYROX = rawGX[1] | rawGX[0]<<8;

  //==================================================
  Wire.beginTransmission(ADDRESS);
  Wire.write(GYRO_YOUT_H);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS,2,1);
  for(int i = 0; i<2 ; i++)
  {
    rawGY[i] = Wire.read();
  }
  rawGYROY = rawGY[1] | rawGY[0]<<8;


  //==================================================
  Wire.beginTransmission(ADDRESS);
  Wire.write(GYRO_ZOUT_H);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS,2,1);
  for(int i = 0; i<2 ; i++)
  {
    rawGZ[i] = Wire.read();
  }
  rawGYROZ = rawGZ[1] | rawGZ[0]<<8;
}
