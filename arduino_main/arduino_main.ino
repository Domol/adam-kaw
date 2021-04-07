 
   ///////////////////////////////////////////
  //             © NIEUŻYTEK ROLNY         //
 //                 studios               //
///////////////////////////////////////////

#define DEBUG
#include <SPI.h>
#include <MFRC522.h>


// GLOBALS
const byte numReaders = 3;

const byte ssPins[] = {2,3,4};
const byte resetPin = 8;
const byte openLed = 6;

MFRC522 mfrc522[numReaders];

// sequence of RFID readers solving puzzle TODO
const String correctIDs[] = {"201853c3","1a2c52c3","a17a9c73"};

String currentIDs[numReaders];

const byte lockPin = A0;



void onSolve() {
  #ifdef DEBUG
  // Print debug info
  Serial.println(F("Puzzle Solved!"));
  #endif
  // Release the lock
  digitalWrite(lockPin, HIGH);
  digitalWrite(openLed, HIGH);
}
 
void setup() {
  // put your setup code here, to run once:
  #ifdef DEBUG
  //init serial communications channel with the PC
  Serial.begin(9600);
  Serial.println(F("Serial communication started"));
  #endif

  // Set lock pin as output and secure the lock.
  pinMode(lockPin, OUTPUT);
  digitalWrite(lockPin, LOW);
  pinMode(openLed, OUTPUT);
  digitalWrite(openLed, LOW);
  

  // Initialize the SPI bus
  SPI.begin();

  for(uint8_t i=0; i<numReaders; i++) {
     mfrc522[i].PCD_Init(ssPins[i], resetPin);
     // set antenna gain to max (check if works)
     mfrc522[i].PCD_SetAntennaGain(MFRC522::PCD_RxGain::RxGain_max);

     // Dubug info
     Serial.print(F("Reader #"));
     Serial.print(i);
     Serial.print(F("initialized on pin "));
     Serial.print(String(ssPins[i]));
     Serial.print(F(". Antenna strength: "));
     Serial.print(mfrc522[i].PCD_GetAntennaGain());
     Serial.print(F(". Version: "));
     mfrc522[i].PCD_DumpVersionToSerial();

  }
  Serial.println(F("---- END SETUP ----"));
}

void loop() {
  // Assume that the puzzle has been solved
  boolean puzzleSolved = true;


  // Assume that the tags have not changed since last reading
  boolean changedValue = false;
  for (uint8_t i=0; i<numReaders; i++) {
    mfrc522[i].PCD_Init();
//    Serial.print(i);
    String readRFID = "";
    // If sensor detects a tag and is able to read it
    if(mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
      readRFID = "";
      for ( uint8_t j = 0; j < 4; j++) { // The MIFARE PICCs that we use have 4 byte UID
        readRFID.concat(String(mfrc522[i].uid.uidByte[j], HEX)); // Adds the 4 bytes in a single String variable
      }

      if( readRFID != currentIDs[i]) {
        // Set flag to show that puzzle state has changed
        changedValue = true;
        currentIDs[i] = readRFID;
      }

        // If reading fails to match the corrent ID for this sensor
//        Serial.println(F("current"));
//        Serial.println(currentIDs[i]);
//        Serial.println(F("correct"));
//        Serial.println(correctIDs[i]);
      if(currentIDs[i] != correctIDs[i]) {
        //TODO tutaj można te diody włączać/wyłączać
        puzzleSolved = false;
      }
    }

    if(currentIDs[i] != correctIDs[i]) {
      //TODO tutaj można te diody włączać/wyłączać
      puzzleSolved = false;
    }
    //HAlt PICC
    mfrc522[i].PICC_HaltA();
    mfrc522[i].PCD_StopCrypto1();
  }

  //IF the changedValue flag has been set, at least one sensor has changed;
  if(changedValue) {
    //Dump serial to the current state of all sensors
    for(uint8_t i=0; i<numReaders; i++) {
      Serial.print(F("Reader #"));
      Serial.print(String(i));
      Serial.print(F(" on Pin #"));
      Serial.print(String((ssPins[i])));
      Serial.print(F(" detected tag: "));
      Serial.print(currentIDs[i]);
    }
    
    Serial.println(F("---"));
    Serial.println(puzzleSolved);
    if(puzzleSolved) {
      onSolve();
    }
  }
  //add short delay before next polling sensors
  delay(200);
}
