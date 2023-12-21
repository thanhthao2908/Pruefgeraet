/*
% Aditor: Thi Thanh Thao Tran
% letzte Änderung:  24-10-2022  
% Version: V1.1   
% Status: fertig - läufähig
% Speicherort: 
% MATLAB Code für den Prüfer (Arduino Nano33BLE)
% Ziel: Test Funktionsfähigkeit eines Arduino Boards
%-----------------------------------------------------------------------
*/

#include <ArduinoBLE.h>




//String inString;
int incomingByte;
//int inPin;
//int flag = false;

void controlLed(BLEDevice peripheral);
void characteristic_Callback (BLECharacteristic characteristic);

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

  characteristic.writeValue((byte)0x01);
          if (digitalRead(2) == HIGH) {

            delay(100);
            characteristic.writeValue((byte)0x02);
            if (digitalRead(2) == LOW){
              Serial.println("Pin D2: In Ordnung!!!");
            } 
          }
          else Serial.println("Pin D2: Kaputt!!!");
          
          characteristic.writeValue((byte)0x03);
            if (digitalRead(3) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x04);
              if (digitalRead(3) == LOW){
                Serial.println("Pin D3: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D3: Kaputt!!!");

            characteristic.writeValue((byte)0x05);
            if (digitalRead(4) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x06);
              if (digitalRead(4) == LOW){
                Serial.println("Pin D4: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D4: Kaputt!!!");

            characteristic.writeValue((byte)0x07);
            if (digitalRead(5) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x08);
              if (digitalRead(5) == LOW){
                Serial.println("Pin D5: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D5: Kaputt!!!");

            characteristic.writeValue((byte)0x09);
            if (digitalRead(6) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x0a);
              if (digitalRead(6) == LOW){
                Serial.println("Pin D6: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D6: Kaputt!!!");

            characteristic.writeValue((byte)0x0b);
            if (digitalRead(7) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x0c);
              if (digitalRead(7) == LOW){
                Serial.println("Pin D7: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D7: Kaputt!!!");

            characteristic.writeValue((byte)0x0d);
            if (digitalRead(8) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x0e);
              if (digitalRead(8) == LOW){
                Serial.println("Pin D8: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D8: Kaputt!!!");

            characteristic.writeValue((byte)0x0f);
            if (digitalRead(9) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x10);
              if (digitalRead(9) == LOW){
                Serial.println("Pin D9: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D9: Kaputt!!!");

            characteristic.writeValue((byte)0x11);
            if (digitalRead(10) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x12);
              if (digitalRead(10) == LOW){
                Serial.println("Pin D10: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D10: Kaputt!!!");

            characteristic.writeValue((byte)0x13);
            if (digitalRead(11) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x14);
              if (digitalRead(11) == LOW){
                Serial.println("Pin D11: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D11: Kaputt!!!");

            characteristic.writeValue((byte)0x15);
            if (digitalRead(12) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x16);
              if (digitalRead(12) == LOW){
                Serial.println("Pin D12: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D12: Kaputt!!!");

            characteristic.writeValue((byte)0x17);
            if (digitalRead(13) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x18);
              if (digitalRead(13) == LOW){
                Serial.println("Pin D13: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin D13: Kaputt!!!");

            characteristic.writeValue((byte)0x19);
            if (digitalRead(A0) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x1a);
              if (digitalRead(A0) == LOW){
                Serial.println("Pin A0: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A0: Kaputt!!!");

            characteristic.writeValue((byte)0x1b);
            if (digitalRead(A1) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x1c);
              if (digitalRead(A1) == LOW){
                Serial.println("Pin A1: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A1: Kaputt!!!");
          
            characteristic.writeValue((byte)0x1d);
            if (digitalRead(A2) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x1e);
              if (digitalRead(A2) == LOW){
                Serial.println("Pin A2: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A2: Kaputt!!!");
          
            characteristic.writeValue((byte)0x1f);
            if (digitalRead(A3) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x20);
              if (digitalRead(A3) == LOW){
                Serial.println("Pin A3: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A3: Kaputt!!!");
          
            characteristic.writeValue((byte)0x21);
            if (digitalRead(A4) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x22);
              if (digitalRead(A4) == LOW){
                Serial.println("Pin A4: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A4: Kaputt!!!");

            characteristic.writeValue((byte)0x23);
            if (digitalRead(A5) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x24);
              if (digitalRead(A5) == LOW){
                Serial.println("Pin A5: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A5: Kaputt!!!");

            characteristic.writeValue((byte)0x25);
            if (digitalRead(A6) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x26);
              if (digitalRead(A6) == LOW){
                Serial.println("Pin A4: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A4: Kaputt!!!");

            characteristic.writeValue((byte)0x27);
            if (digitalRead(A7) == HIGH) {

              delay(100);
              characteristic.writeValue((byte)0x28);
              if (digitalRead(A7) == LOW){
                Serial.println("Pin A7: In Ordnung!!!");
              } 
            }
            else Serial.println("Pin A7: Kaputt!!!");
}

      /*
      //Check jede Pin
      
      if (isDigit(inChar)){
        inString += (char)inChar; // convert the incoming byte to a char and add it to the string: 
      }

      if (inChar == '\n') {
        Serial.println(inString.toInt()); 
        Serial.print("Pin ");
        inPin = inString.toInt();
        Serial.print(inPin);

        switch (inPin) {
          case 2: 
            characteristic.writeValue((byte)0x01);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x02);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 3: 
            characteristic.writeValue((byte)0x03);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x04);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              }
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 4: 
            characteristic.writeValue((byte)0x05);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x06);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 5: 
            characteristic.writeValue((byte)0x07);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x08);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 6: 
            characteristic.writeValue((byte)0x09);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x10);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 7: 
            characteristic.writeValue((byte)0x11);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x12);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 8: 
            characteristic.writeValue((byte)0x13);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x14);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;
          
          case 9: 
            characteristic.writeValue((byte)0x15);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x16);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;
    
          case 10: 
            characteristic.writeValue((byte)0x17);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x18);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;
          
          case 11: 
            characteristic.writeValue((byte)0x19);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x20);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;
          
          case 12: 
            characteristic.writeValue((byte)0x21);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x22);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;
          
          case 13: 
            characteristic.writeValue((byte)0x23);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x24);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 16: 
            characteristic.writeValue((byte)0x25);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x26);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              } 
            }
            else Serial.println(": Kaputt!!!");
            inString = "";
          break;

          case 17: 
            characteristic.writeValue((byte)0x27);
            if (digitalRead(inPin) == HIGH) {
              characteristic.writeValue((byte)0x28);
              if (digitalRead(inPin) == LOW){
                Serial.println(": In Ordnung!!!");
              }
            } 
            else Serial.println(": Kaputt!!!"); 
            inString = "";
          break;
          
          //Mehrere
          
          default: 
            Serial.println(" ");
            Serial.println("Schalten Sie die Pinport bitte!!!");
            inString = "";
          break;
        } 
      } 
    }
  }
  Serial.println("Peripheral disconnected");
}
*/