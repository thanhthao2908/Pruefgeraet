/*
Aditor: Thi Thanh Thao Tran
Letzte Änderung:  15-11-2022  
Version: V1.2.2 (end)
Status: fertig - läufähig
Speicherort: 
MATLAB Code für den Prüfling (Arduino Nano33BLE)
Ziel: Test Funktionsfähigkeit eines Arduino Nano33BLE Boards
%-----------------------------------------------------------------------
*/

#include <Arduino.h>
#include <ArduinoBLE.h>

BLEService DeviceService("19B10000-E8F2-537E-4F6C-D104768A1214");                                        //Die UUID der Prüfling definieren

BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);  //Die UUID der Eingenschaften definiere , lesbar und beschreibbar

void writecharacteristic(byte pin);                                         //Funktion für Erstellung der Eigenschaften der Prüfling

byte pin;                                                                   //Pinvariable initialisieren
char val = '1';                                                             //Neutrale Daten von Prüflung/Prüfgerät zur Prüfung Tx/Rx initialisieren 

void setup() {
  
  Serial.begin(9600);
  Serial1.begin(9600);

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

  
  if (!BLE.begin()) {                                                                     // begin initialization
    //Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Nano33BLESLAVE");                                                     //Name der Prüflingsgerät umbenennen
  BLE.setAdvertisedService(DeviceService);                                                //Advertise der Bluetooth konfigugieren 

  DeviceService.addCharacteristic(switchCharacteristic);                                  //Eigenschaft hinzufügen

  BLE.addService(DeviceService);                                                          //Service hinzufügen

  switchCharacteristic.writeValue(0);                                                     //Anfangswerts für die Eigenschaft festlegen

  BLE.advertise();                                                                        //Advertise der Bluetooth starten 

  //Serial.println("Arduino Nano 33 BLE (Peripheral)");
  //Serial.println(" "); 
  
}

void loop() {

  Serial.println("Hier ist der Test Serial0 ! ");                                         //Ausgabe zum Test der Serial0 pin
  //Serial1.println("Hier ist der Test Serial1 ! ");                                      //Ausgabe zum Serial1

  BLEDevice central = BLE.central();
  //Serial.println("Connected to central device!");
  if (central) {
    //Serial.println("Connected to central device!");

    //Serial.println("----------------------------------------------------------------------");

    while (central.connected()) {                                                         //Während die Prüflingsgerät mit der Prüfgerät verbindet, dann
      
      if (switchCharacteristic.written()) {                                               //prüfen, wenn die Prüflingsgerät zur Eigenschaft schreibt, dann
        pin = switchCharacteristic.value();                                               //nutzt diese Wert zum Kontrol der Pins  
        writecharacteristic(pin);                                                         //rurf die Funktion auf mit Übergabewert Pin
      }
    }

    //Serial.print("Disconnected from central: ");
    //Serial.println(central.address());
  }
}

void writecharacteristic(byte pin) {
  
  switch (pin) {
    case 0x01:digitalWrite(2,HIGH);break;                                                //Pin D2 einsetzen
    case 0x02:digitalWrite(2,LOW);break;                                                 //Pin D2 aussetzen
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
    /*Test Rx und Tx sind möglich nur in der Fall Serial1 pin okay. Zum Test sollen die Prüfling durch USBKabel mit dem Host verbunden und testen.*/
    case 0x29:
      Serial1.write(val);
      
    break;                                        //Test Tx: Sending Data der Prüfling
    case 0x2a: 
      if (Serial1.read() == val) {                                             //Test Rx: Recieving Data der Prüfling
        //Serial.println("Serial1 Rx pin ist in Ordnung!");
        Serial1.write(val);
      }
    break;
    //Mehrere
    default: 
    break;
  }      
}
