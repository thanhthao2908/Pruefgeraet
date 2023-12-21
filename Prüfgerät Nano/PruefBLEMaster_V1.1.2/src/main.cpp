/*
% Aditor: Thi Thanh Thao Tran
% letzte Änderung:  04-11-2022  
% Version: V1.1.2   
% Status: fertig - läufähig
% Speicherort: 
% MATLAB Code für den Prüfer (Arduino Nano33BLE)
% Ziel: Test Funktionsfähigkeit eines Arduino Boards
%-----------------------------------------------------------------------
*/
#include <Arduino.h>
#include <ArduinoBLE.h>

#define time1 100                                                //Abwartezeit definieren
#define anzahl_Pin 20                                           //Summe der Pins auf Arduino Nano33BLE Board definieren

int incomingByte;
int zeiger = anzahl_Pin - 1;                                    //Bitstelle initialisieren und gleich Bit an 19.Pos (20.Bit von rechts)

String array_prognose[anzahl_Pin] = {                           //Array für die Prognoseausgaben
  "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", 
  "D10", "D11", "D12", "D13", "A0", "A1", 
  "A2", "A3", "A4", "A5", "A6", "A7"                            //Bit von A7 wird in der niedrigsten Bitstelle der result
};

void controlLed(BLEDevice peripheral);
void characteristic_Callback (BLECharacteristic characteristic);
bool readPin (uint8_t pin);

void setup() {

  Serial.begin(9600);
  while (!Serial);
 
  pinMode(2, INPUT); 
  pinMode(3, INPUT); 
  pinMode(4, INPUT); 
  pinMode(5, INPUT); 
  pinMode(6, INPUT); 
  pinMode(7, INPUT); 
  pinMode(8, INPUT); 
  pinMode(9, INPUT); 
  pinMode(10, INPUT); 
  pinMode(11, INPUT); 
  pinMode(12, INPUT); 
  pinMode(13, INPUT); 

  pinMode(A0, INPUT); 
  pinMode(A1, INPUT); 
  pinMode(A2, INPUT); 
  pinMode(A3, INPUT); 
  pinMode(A4, INPUT); 
  pinMode(A5, INPUT); 
  pinMode(A6, INPUT); 
  pinMode(A7, INPUT); 


  BLE.setLocalName("Nano33BLEMASTER"); 
  BLE.advertise();
  BLE.begin();
  
  Serial.println("Arduino Nano 33 BLE (Central Device)");

  Serial.println("Discovering peripheral device.......");
  Serial.println(BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214"));
  
}

void loop() {
  // check if a peripheral has been discovered
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    // discovered a peripheral, print out address, local name, and advertised service
    if (peripheral) {
    Serial.println("Peripheral device found!");
    //Serial.print("Device MAC address: ");
    //Serial.println(peripheral.address());
    //Serial.print("Device name: ");
    //Serial.println(peripheral.localName());
    //Serial.print("Advertised service UUID: ");
    //Serial.println(peripheral.advertisedServiceUuid());
    //Serial.println(" ");

    if (peripheral.localName() != "Nano33BLESLAVE") {
      return;
    }
  }

    BLE.stopScan();

    controlLed(peripheral);

    BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");
  }
}

void controlLed(BLEDevice peripheral) {
  Serial.println("Connecting to peripheral device...");
  Serial.println("----------------------------------------------------------------------");

  if (peripheral.connect()) {
    Serial.println("Connected to peripheral device!");
    Serial.println(" ");
  } else {
    Serial.println("Connection to peripheral device failed!");
    Serial.println(" ");
    return;
  }
  
  
  Serial.println("Discovering peripheral device attributes...");
  if (peripheral.discoverAttributes()) {
    Serial.println("Peripheral device attributes discovered!");
    Serial.println(" ");
  } else {
    Serial.println("Peripheral device attributes discovery failed!");
    Serial.println(" ");
    peripheral.disconnect();
    return;
  }
  

  BLECharacteristic characteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");

  if (!characteristic) {
    Serial.println("Peripheral does not have PIN characteristic!");
    peripheral.disconnect();
    return;
  } else if (!characteristic.canWrite()) {
    Serial.println("Peripheral does not have a writable PIN characteristic!");
    peripheral.disconnect();
    return;
  }

  Serial.println(" ");
  Serial.println("Haben Sie die Arduino auf Brett schaten? 1: yes 0: no");

  while (peripheral.connected()) {
      // while the peripheral is connected

    if (Serial.available()){
      // Read serial input:
      //int inChar = Serial.read(); 
      int incomingByte = Serial.read();

      if (incomingByte == '1') {
        Serial.println("Test started!!!");
        delay(1000);

        characteristic_Callback (characteristic);
      }

        else Serial.println("Schalten Sie die Pinport bitte !!!");  
    } 
  }
  Serial.println("Peripheral disconnected");   
}

void characteristic_Callback (BLECharacteristic characteristic) {

  uint8_t i = 1;
  uint8_t j = 1;

  while (i <= 20) {

    characteristic.writeValue((byte)j);
    delay(time1);
    if (readPin(i) == 1) {

      j++;
      characteristic.writeValue((byte)j);
      delay(time1);
      if (readPin(i) == 0){

        Serial.print("Pin ");
        Serial.print(array_prognose[zeiger]);
        Serial.println(": In Ordnung!!!");
      } 
    }
    else {

      Serial.print("Pin ");
      Serial.print(array_prognose[zeiger]);
      Serial.println(": Defekt!!!");
    }

    i++;
    j++;
    zeiger = zeiger - 1;
  }
}

bool readPin (uint8_t pin) {

  bool status;
  switch (pin) {

    case 0x01:status = digitalRead(2);break;                           //digitale Pins
    case 0x02:status = digitalRead(3);break;                           
    case 0x03:status = digitalRead(4);break;
    case 0x04:status = digitalRead(5);break;
    case 0x05:status = digitalRead(6);break;
    case 0x06:status = digitalRead(7);break;
    case 0x07:status = digitalRead(8);break;
    case 0x08:status = digitalRead(9);break;
    case 0x09:status = digitalRead(10);break;
    case 0x0a:status = digitalRead(11);break;
    case 0x0b:status = digitalRead(12);break;
    case 0x0c:status = digitalRead(13);break;
    case 0x0d:status = digitalRead(A0);break;                          //analoge Pins
    case 0x0e:status = digitalRead(A1);break;
    case 0x0f:status = digitalRead(A2);break;
    case 0x10:status = digitalRead(A3);break;
    case 0x11:status = digitalRead(A4);break;
    case 0x12:status = digitalRead(A5);break;
    case 0x13:status = digitalRead(A6);break;
    case 0x14:status = digitalRead(A7);break;

    //Mehrere
    default: 
    break;
  }
  return status; 
}

      