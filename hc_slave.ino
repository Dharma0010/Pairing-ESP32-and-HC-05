#include <SoftwareSerial.h>

#define RX 10 // inverse Rx--->Tx 
#define TX 11 // inverse Tx<---Rx

SoftwareSerial SerialBT(RX, TX);
int Value=0;
String ValueSlave;
int ValueSlaveInt;

void setup(){
  Serial.begin(9600);
  SerialBT.begin(9600);
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if(SerialBT.available()){
      ValueSlave  =SerialBT.readStringUntil('\n');
      ValueSlaveInt = ValueSlave.toInt();
      Serial.print("Data Dari Master : ");
      Serial.println(ValueSlaveInt);
  }
}
