/*
Aditor: Thi Thanh Thao Tran
Letzte Änderung:  24-10-2022  
Version: V1.1   
Status: fertig - läufähig
Speicherort: 
MATLAB Code für den Prüfling (Arduino Nano33BLE)
Ziel: Test Funktionsfähigkeit eines Arduino Boards
%-----------------------------------------------------------------------
*/

#include <ArduinoBLE.h>

BLEService DeviceService("19B10000-E8F2-537E-4F6C-D104768A1214"); 

BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void writecharacteristic(byte pin);

byte pin;

void setup() {
  //Serial.begin(9600);
  //while (!Serial);

  // set pin to output mode
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT); 
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    //Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Nano33BLESLAVE");
  BLE.setAdvertisedService(DeviceService);

  DeviceService.addCharacteristic(switchCharacteristic);

  BLE.addService(DeviceService);

  switchCharacteristic.writeValue(0);

  BLE.advertise();

  Serial.println("Arduino Nano 33 BLE (Peripheral)");
  Serial.println(" ");
}

void loop() {
  
  BLEDevice central = BLE.central();

  if (central) {
    //Serial.println("Connected to central device!");

    //Serial.println("----------------------------------------------------------------------");

    while (central.connected()) {
      
      if (switchCharacteristic.written()) {
        pin = switchCharacteristic.value();  
        writecharacteristic(pin);
      }
    }

    //Serial.print("Disconnected from central: ");
    //Serial.println(central.address());
  }
}

void writecharacteristic(byte pin) {
  
   switch (pin) {
      case 0x01:digitalWrite(2,HIGH);break;
      case 0x02:digitalWrite(2,LOW);break;
      case 0x03:digitalWrite(3,HIGH);break;
      case 0x04:digitalWrite(3,LOW);break;
      case 0x05:digitalWrite(4,HIGH);break;
      case 0x06:digitalWrite(4,LOW);break;
      case 0x07:digitalWrite(5,HIGH);break;
      case 0x08:digitalWrite(5,LOW);break;
      case 0x09:digitalWrite(6,HIGH);break;
      case 0x0a:digitalWrite(6,LOW);break;
      case 0x0b:digitalWrite(7,HIGH);break;
      case 0x0c:digitalWrite(7,LOW);break;
      case 0x0d:digitalWrite(8,HIGH);break;
      case 0x0e:digitalWrite(8,LOW);break;
      case 0x0f:digitalWrite(9,HIGH);break;
      case 0x10:digitalWrite(9,LOW);break;
      case 0x11:digitalWrite(10,HIGH);break;
      case 0x12:digitalWrite(10,LOW);break;
      case 0x13:digitalWrite(11,HIGH);break;
      case 0x14:digitalWrite(11,LOW);break;
      case 0x15:digitalWrite(12,HIGH);break;
      case 0x16:digitalWrite(12,LOW);break;
      case 0x17:digitalWrite(13,HIGH);break;
      case 0x18:digitalWrite(13,LOW);break;

      case 0x19:digitalWrite(A0,HIGH);break;
      case 0x1a:digitalWrite(A0,LOW);break;
      case 0x1b:digitalWrite(A1,HIGH);break;
      case 0x1c:digitalWrite(A1,LOW);break;
      case 0x1d:digitalWrite(A2,HIGH);break;
      case 0x1e:digitalWrite(A2,LOW);break;
      case 0x1f:digitalWrite(A3,HIGH);break;
      case 0x20:digitalWrite(A3,LOW);break;
      case 0x21:digitalWrite(A4,HIGH);break;
      case 0x22:digitalWrite(A4,LOW);break;
      case 0x23:digitalWrite(A5,HIGH);break;
      case 0x24:digitalWrite(A5,LOW);break;
      case 0x25:digitalWrite(A6,HIGH);break;
      case 0x26:digitalWrite(A6,LOW);break;
      case 0x27:digitalWrite(A7,HIGH);break;
      case 0x28:digitalWrite(A7,LOW);break;
      
      //Mehrere
      default: 
      break;
    }      
}
