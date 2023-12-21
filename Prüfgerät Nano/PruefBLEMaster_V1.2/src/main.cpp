/*
% Aditor: Thi Thanh Thao Tran
% letzte Änderung:  07-11-2022  
% Version: V1.2 (end)
% Status: fertig - läufähig
% Speicherort: 
% MATLAB Code für den Prüfer (Arduino Nano33BLE)
% Ziel: Test Funktionsfähigkeit eines Arduino Nano33BLE Boards
%-----------------------------------------------------------------------
*/

#include <Arduino.h>
#include <ArduinoBLE.h>

#define time1 20                                                //Abwartezeit definieren
#define anzahl_Pin 22                                           //Summe der Pins auf Arduino Nano33BLE Board definieren

String array_prognose[anzahl_Pin] = {                           //Array für die Prognoseausgaben
  "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", 
  "D10", "D11", "D12", "D13", "A0", "A1", 
  "A2", "A3", "A4", "A5", "A6", "A7"                //Bit von Rx wird in der niedrigsten Bitstelle der result
};                                                                                                                       

unsigned char input;                                            //Eingabebuchstabe zum Start initialisieren                                                 
int anzahl_defekt;                                              //Anzahl der defekte Pins initialisieren
int zeiger;                                                     //Bitstelle initialisieren 
u_int32_t result;                                               //Ergebnis initialisieren


void controlPin(BLEDevice peripheral);                          //Kontrollsfunktion vom Prüfgerät definieren
void list();
void characteristic_Callback (BLECharacteristic characteristic);//Funktion für Erstellung neuer Charaktereigenschaften definieren
bool readPin (uint8_t pin);                                     //Funktion für Lesen der Eingängen Pins definieren
int countDefekt (u_int32_t result);                             //Zählenfunktion defektter Pins definieren
void printDefekt (u_int32_t result);                            //Ausgabefunktion für bestimmten defektten Pins definieren


void setup() {

  Serial.begin(9600);                                          
  while (!Serial);
 
  pinMode(2, INPUT);                                              //Setzen alle digitalen Pins als Eingänge
  pinMode(3, INPUT);                                              //
  pinMode(4, INPUT);                                              //
  pinMode(5, INPUT);                                              
  pinMode(6, INPUT); 
  pinMode(7, INPUT); 
  pinMode(8, INPUT); 
  pinMode(9, INPUT); 
  pinMode(10, INPUT); 
  pinMode(11, INPUT); 
  pinMode(12, INPUT); 
  pinMode(13, INPUT); 

  pinMode(A0, INPUT);                                              //Setzen alle analogen Pins als Eingänge
  pinMode(A1, INPUT);                                              //
  pinMode(A2, INPUT);                                              //
  pinMode(A3, INPUT); 
  pinMode(A4, INPUT); 
  pinMode(A5, INPUT); 
  pinMode(A6, INPUT); 
  pinMode(A7, INPUT); 


  BLE.setLocalName("Nano33BLEMASTER");                                      //Name der Prüflingsgerät umbenennen
  BLE.advertise();                                                          //Advertise der Bluetooth starten 
  BLE.begin();                                                              //Initialisieren der Bluetooth® Low Energy-Hardware
  
  Serial.println("Arduino Nano 33 BLE (Central Device)");                   //
  Serial.println("Discovering peripheral device.......");
  BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");                  //Start das Scannen nach Peripheriegeräten
  
}

void loop() {
  
  BLEDevice peripheral = BLE.available();                                   //Abfrage nach die Verfügbarskeit von anderen BLE-Geräten

  if (peripheral) {                                                         //Erkennen eines Peripheriegeräts
    
    Serial.println("Peripheral device found!");
    
    if (peripheral.localName() != "Nano33BLESLAVE")                         //die nicht richtigen suchenchenden Geräte ignorieren
    return;

    BLE.stopScan();                                                         //Stop das Scannen

    controlPin(peripheral);                                                 //Aufruf des Kontrollprogramms

    BLE.scanForUuid("19b10000-e8f2-537e-4f6c-d104768a1214");                //Wiederholen das Scannen nach Peripheriegeräten, wenn Peripheriegerät getrennt wurde
  }
}

void controlPin(BLEDevice peripheral) {                                     //Kontroll des Peripheriegerät

  if (peripheral.connect()) {                                               //Anschließen an das Peripheriegerät
    
    Serial.println("Connected to peripheral device!");                      //
  } else {

    Serial.println("Connection to peripheral device failed!");              //Melden, wenn Verbindung zum Peripheriegerät fehlgeschlagen ist!
    return;
  }
  
  
  if (peripheral.discoverAttributes()) {                                    //Erkennen von Peripherieattributen
    
    //Serial.println("Peripheral device attributes discovered!");           //
  } else {
    
    Serial.println("Peripheral device attributes discovery failed!");       //Melden, wenn Die Erkennung von Attributen für Peripheriegeräte fehlgeschlagen ist !
    Serial.println("Peripheral disconnected");                                                   //Melden, wenn Peripheriegerät getrennt wird !
    Serial.println("\n");
    peripheral.disconnect();                                                //Peripheriegerät trennen
    return;
  }

  BLECharacteristic characteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214"); //Abrufen die PIN-Eigenschaften

  if (!characteristic) {                                                                                //Melden, wenn Peripheriegerät keine PIN-Eigenschaften hat !
    
    Serial.println("Peripheral does not have PIN characteristic!");
    Serial.println("Peripheral disconnected");                                                   //Melden, wenn Peripheriegerät getrennt wird !
    Serial.println("\n");
    peripheral.disconnect();                                                                            //Peripheriegerät trennen
    return;
  } 
  else if (!characteristic.canWrite()) {                                                                //Melden, wenn Peripheriegerät keine beschreibbare PIN-Eigenschaften hat!
    
    Serial.println("Peripheral does not have a writable PIN characteristic!");
    Serial.println("Peripheral disconnected");                                                   //Melden, wenn Peripheriegerät getrennt wird !
    Serial.println("\n");
    peripheral.disconnect();                                                                            //Peripheriegerät trennen
    return;
  }

  /*-------------------------------------------------------------------------------------------*/

  Serial.println(" ");
  
  list();                                                                                    //list() aufrufen

  while (peripheral.connected()) {                                                           // während das Peripheriegerät angeschlossen ist
    
    if (Serial.available()){
      
      input = Serial.read(); 
      //Serial.println((char) input);                                                                

      switch (input) {
         
        case 'h': 
          Serial.print("Die Software dieses Pruefgeraets dient fuer den Test eines anderen Arduino Nano33BLE Boards (Pruefling). ");
          Serial.print("Gebraucht werden ein Nano33BLE Board mit den Pruefstiften, ein USBKabel, Nano33BLE Board und Software fuer die Boards. ");
          Serial.print("Vor dem Test werden die Software ueber USB-Kabel in Boards instaliert. Waehrend des Test muss die Kabel unbedingt mit "); 
          Serial.print("dem Pruefer verbindet werden, kann die Pruefling ohne Kabel durch die Kontakt an den Pruefstiften geprueft werden. ");
          Serial.println("Die Richtungen des Prueflings und des Pruefer sind beruecksichtigt.");
          Serial.print("\n");
        break;

        case 'p':                                                                              //drückt die Peripheriegerät infos aus
          Serial.println("Peripheriegeraet: Arduino Nano33BLE");
          Serial.print("Localname: ");
          Serial.println(peripheral.deviceName());
          Serial.print("UUIP: ");
          Serial.println(peripheral.address());
          Serial.print("AdvertisedServiceUuid: ");
          Serial.println(peripheral.advertisedServiceUuid());
          Serial.print("\n");
        break;   
                                                                            
        case 'c':                                                                              //drückt die Prüfgerät infos aus
          Serial.println("Pruefgeraet: Arduino Nano33BLE");
          Serial.print("Localname: ");
          Serial.println("Nano33BLEMASTER");
          Serial.print("\n");
        break;

        case 's':                                                                              //start den Test
          delay(500);
          Serial.println("Test started!!!");
          characteristic_Callback (characteristic);                                            //Aufruf das PIN-Charaktereigenschaften
        break;

        default:
          //list();
        break;     
      }
    }
  }
  
  Serial.println("Peripheral disconnected");                                                   //Melden, wenn Peripheriegerät getrennt wird !
  Serial.println("\n");
}

void list () {

  Serial.println("h: Help");
  Serial.println("p: Infos vom Peripheriegeraet");
  Serial.println("c: Infos vom Pruefgeraet");
  Serial.println("s: Start den Test");
  Serial.println("-------------------------------");
  Serial.print("\n");

}

void characteristic_Callback (BLECharacteristic characteristic) {       //neue Charaktereigenschaften erstellen
    
  result = 0x00000000;                                       //lokale Variable definieren

  uint8_t i = 1;                                             //Bitstelle initialisieren, für Kontrolgerät
  uint8_t j = 1;                                             //für Peripheriegerät

  while (i <= (anzahl_Pin - 2)) {                            //bezüglich 2 Pin Rx und Tx
    
    result = result << 1;
    characteristic.writeValue((byte)j);                      //Kontroll: Pins von Prüfling einsetzen
    delay(time1);                                            //Abwarten  
    if (readPin(i) == HIGH) {                                //Pin von Prüfgerät lesen und mit 1 = HIGH vergleichen, wenn ja, dann 

      j++;
      characteristic.writeValue((byte)j);                    //Kontroll: Pins von Prüfling aussetzen
      delay(time1);                                          //Abwarten
      if (readPin(i) == LOW){                                //Pin von Prüfgerät lesen und mit 0 = LOW vergleichen, wenn ja, dann 

        result = result | 1;                                 //Fügen einen 1 in entsprechender Bitstelle hinzu
      } 
    }else j++; 

    i++;                                                     //Bitstelle i = [0x01, 0x14], 20 Stellen
    j++;                                                     //Bitstelle j = [0x01, 0x28], 40 Stellen 
  }

  anzahl_defekt = countDefekt (result);                      //Aufruf der Zählenfunktion und die Rückgebewert an der Variable abspeichern 
  Serial.print("Anzahl der defekten Pins: ");                                 
  Serial.println(anzahl_defekt);                             //Ausdruck Anzahl der defektte Pins

  if (anzahl_defekt == 0) {                                  //wenn keine Defekt
    
    Serial.println("Alle Pins OK! ");
    Serial.println("\n");
  }
  else {
    
    //Serial.println(result,BIN);
    printDefekt (result);                                   //wenn Defekte vorhanden, ruft die Funktion Defektsausgabe auf  
    Serial.println("\n");
  }
}

bool readPin (uint8_t pin) {                                 //Lesen die Eingänge Pins

  bool status;
  switch (pin) {

    case 0x01:status = digitalRead(2);break;                 //digitale Pins
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
    case 0x0d:status = digitalRead(A0);break;                //analoge Pins
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
  return status;                                             //Rückgabewert 1 = HIGH oder 0 = LOW
}

int countDefekt (u_int32_t result) {                         //Zählenfunktion mit Rückgabewert 

  u_int32_t copy_result_1 = result;                          //lokale Variable
  int defekt = 0;                                            //               

  for (int i = 0; i < anzahl_Pin; i++) {  
    
    if ((copy_result_1 & 1) == 0) {                          //Vergleich bits bwz. defekt an A7 erste Bit von rechts --> (result = 0x000ffffe & 0x00000001) == 0x00000000 
                                                                              
      defekt = defekt + 1;                                   //Defektte Pins inkrementieren
    }

    copy_result_1 = copy_result_1 >> 1;                      //nach rechs 1 Stelle verschieben 
  }
  return defekt;                                             //Rückgabewert
}

void printDefekt (u_int32_t result) {                        //Defektsausgabe Funktion

  u_int32_t copy_result_2 = result;                          //lokale Variable

  for (int i = 0; i < anzahl_Pin; i++) {                     //Bitstelle dekrementieren
    
    zeiger = (anzahl_Pin - i) - 1;                            

    if ((copy_result_2 & 1) == 0) {                          //erste Bit von recht mit 0 vergleichen, wenn 0, druckt die entsprechende Pin aus 

      Serial.print(array_prognose[zeiger]);                  //globale Variable, oben definieren
      Serial.print(" ");
    }
    
    copy_result_2 = copy_result_2 >> 1;                      //nach rechs 1 Stelle verschieben
  } 
}