#include<SoftwareSerial.h>
SoftwareSerial BTserial(2,3);
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int l,r,m,i,t= 0;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //Begin serial communication

 Wire.begin();
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x6B);  // PWR_MGMT_1 register
 Wire.write(0);     // set to zero (wakes up the MPU-6050)
 Wire.endTransmission(true);

pinMode(5,OUTPUT);
pinMode(7,OUTPUT);
pinMode(9,OUTPUT);
pinMode(11,OUTPUT);
pinMode(13,OUTPUT);
pinMode(22,OUTPUT);
pinMode(24,OUTPUT);
pinMode(26,OUTPUT);
pinMode(28,OUTPUT);
pinMode(39,OUTPUT);
digitalWrite(5,HIGH);
digitalWrite(7,HIGH);
digitalWrite(9,HIGH);
digitalWrite(11,HIGH);
digitalWrite(13,HIGH);
digitalWrite(22,LOW);
digitalWrite(24,LOW);
digitalWrite(26,LOW);
digitalWrite(28,LOW);
digitalWrite(30,LOW);

}

void loop() 
{
  // put your main code here, to run repeatedly:
l=analogRead(A4);
//Serial.print(l);
//Serial.print("  ");
r=analogRead(A3);
//Serial.print(r);
//Serial.print("  ");
m=analogRead(A5);
//Serial.print(m);
//Serial.print("  ");
i=analogRead(A1);
//Serial.print(i);
//Serial.print("  ");
t=analogRead(A7);
//Serial.print(t);
//Serial.println("  ");

/*if (i<330) {
  if (m>380) {
    Serial.println("L");
  }
  else {
    if (l>480) {
      Serial.println("W");
    }
    else {
      if (t>350) {
      Serial.println("B");
      }
  }
  }
}


else if (i>330) {
  if ( m<380) {
    Serial.println("F");
  }
  else {
    if (m> 380) {
      Serial.println("M");
    }
    else {
      if (r<400) {
        Serial.println("V");
      }
      else {
        if (l<480) {
          Serial.println("I");
        }
        else {
          if (t<310) {
            Serial.println("A");
          }
          else {
            Serial.println("M");
          }
        }
      }
    }
  }
}


else {
  Serial.println("DSA");
}
*/
 Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//  Serial.print("AcX = "); Serial.print(AcX);
//  Serial.print(" | AcY = "); Serial.print(AcY);
//  Serial.print(" | AcZ = "); Serial.print(AcZ);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);

  if(r>700 && m<300 && i<350 && AcY<12000)
{
  Serial.println("Start");
}
else if(r>700 && m<300 && i<350 && AcY>12000)
{
  Serial.println("Hello");
}
else if(r>700 && m<300 && i>350 && AcY<12000)
{
  Serial.println("Perfect");
}
else if(r>700 && m<300 && i>350 && AcY>12000)
{
  Serial.println("Not Perfect");
}
else if(r>700 && m>300 && i<350 && AcY<12000)
{
  Serial.println("Washroom");
}
else if(r>700 && m>300 && i<350 && AcY>12000)
{
  Serial.println("No washroom");
}
else if(r<700 && m<300 && i<350 && AcY<12000)
{
  Serial.println("Danger");
}
else if(r<700 && m<300 && i<350 && AcY>12000)
{
  Serial.println("Help");
}
else if(r>700 && m>300 && i>350 && AcY<12000)
{
  Serial.println("Hungry");
}
else if(r>700 && m>300 && i>350 && AcY>12000)
{
  Serial.println("Not hungry");
}
else if(r<700 && m<300 && i>350 && AcY<12000)
{
  Serial.println("Sorry");
}
else if(r<700 && m<300 && i>350 && AcY>12000)
{
  Serial.println("Not sorry");
}
else if(r<700 && m>300 && i<350 && AcY<12000)
{
  Serial.println("All the best");
}
else if(r<700 && m>300 && i<350 && AcY>12000)
{
  Serial.println("Congrats");
}
else if(r<700 && m>300 && i>350 && AcY<12000)
{
  Serial.println("What");
}
else if(r<700 && m>300 && i>350 && AcY>12000)
{
  Serial.println("Water");
}
else
{
  Serial.println("DSA");
}
delay(1500);
}
