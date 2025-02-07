/**
 * Setup platform IO:
 * [env:esp32doit-devkit-v1]
 * platform = espressif32
 * board = esp32dev
 * framework = arduino
 */

// This code only work in esp32 env below 1.0.4

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define LED_STATE_BLUE 2 

#define BTN_1 15  // connect

// mac address HC-05
uint8_t mac_address[6] = { 0x00, 0x23, 0x11, 0x00, 0x68, 0x70 };
const char *pin = "1234";

int Value = 0;
bool connected;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Master", true);
  Serial.println("The device started in master mode, make sure remote BTdevice is on!");
  connected = SerialBT.connect(mac_address);
  SerialBT.setPin(pin);
  
  pinMode(LED_STATE_BLUE, OUTPUT); 
  pinMode(BTN_1, INPUT_PULLUP);

  if(connected) {
    Serial.println("Connected Succesfully!");
  }
  else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
}

void loop() {
  if (SerialBT.hasClient()==true)
    digitalWrite(LED_STATE_BLUE, HIGH);
  else
    digitalWrite(LED_STATE_BLUE, LOW);
  
  if(digitalRead(BTN_1)){
    delay(200);
    if(digitalRead(BTN_1))
      return;
    while (true)
    {
      if(Value<=10){
        SerialBT.println(Value);
        Serial.println(Value);
        Value++;
        delay(1000);
      }
      else {
        Value = Value - 10;
      }
    }
  }
  
}

