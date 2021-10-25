/**************************************************************************/
/*! 
    @file     readMifareClassic.pde
    @author   Adafruit Industries
	@license  BSD (see license.txt)

    This example will wait for any ISO14443A card or tag, and
    depending on the size of the UID will attempt to read from it.
   
    If the card has a 4-byte UID it is probably a Mifare
    Classic card, and the following steps are taken:
   
    Reads the 4 byte (32 bit) ID of a MiFare Classic card.
    Since the classic cards have only 32 bit identifiers you can stick
	them in a single variable and use that to compare card ID's as a
	number. This doesn't work for ultralight cards that have longer 7
	byte IDs!
   
    Note that you need the baud rate to be 115200 because we need to
	print out the data and read from the card at the same time!

This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
This library works with the Adafruit NFC breakout 
  ----> https://www.adafruit.com/products/364
 
Check out the links above for our tutorials and wiring diagrams 
These chips use SPI to communicate, 4 required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (13)
#define PN532_MOSI (11)
#define PN532_SS   (10)
#define PN532_MISO (12)

// If using the breakout or shield with I2C, define just the pins connected
// to the IRQ and reset lines.  Use the values below (2, 3) for the shield!
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield

// Uncomment just _one_ line below depending on how your breakout or shield
// is connected to the Arduino:

// Use this line for a breakout with a SPI connection:
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

// Use this line for a breakout with a hardware SPI connection.  Note that
// the PN532 SCK, MOSI, and MISO pins need to be connected to the Arduino's
// hardware SPI SCK, MOSI, and MISO pins.  On an Arduino Uno these are
// SCK = 13, MOSI = 11, MISO = 12.  The SS line can be any digital IO pin.
//Adafruit_PN532 nfc(PN532_SS);

// Or use this line for a breakout or shield with an I2C connection:
//Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
int assembly =26;
int disassembly =22;
int sort=24;
int feed=28;
int feedcount=0;
int trigger=0;
int redunt=0;
void setup(void) {
  lcd.begin(16,2);
  pinMode(assembly, INPUT);
  pinMode(disassembly, INPUT);
  pinMode(sort, INPUT);
  pinMode(feed, INPUT);
  pinMode (9, OUTPUT);
  digitalWrite(9,LOW);
  Serial.begin(115200);
  while (!Serial) delay(10); // for Leonardo/Micro/Zero

  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
  Serial.println("Waiting for an ISO14443A Card ...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Project is OFF");
}


void loop(void) {
  int rafik= digitalRead(feed);
     while(digitalRead(feed)==1){
      Serial.println("Rafik");
      feedcount=1;  
      }
    /*  if(redunt=1){
        double timers=millis();
        while(millis()-timers<3000){
          feedcount=1;
          redunt=0;
          }
        }*/
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    int rafik= digitalRead(feed);
     while(rafik==1){
       rafik= digitalRead(feed);
      Serial.println("Rafik");
      feedcount=1;  
      }
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    
    if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ... 
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];  
      cardid <<= 8;
      cardid |= uid[3]; 
      Serial.print("Seems to be a Mifare Classic card #");
      Serial.println(cardid);
if(cardid==996785785){
  Serial.print("I am start pin");
digitalWrite(9,HIGH);
trigger=1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Project is ON");
  }
  if(cardid==4039263399){
    Serial.print("I am Status pin");
  //print status
        if(trigger==0){
        double x= millis();
        lcd.clear();
        while(millis()-x<8000){
        lcd.setCursor(2,0);
        lcd.print("Nonmetal in feeding");
        lcd.setCursor(2,1);
        lcd.print("Metal in feeding");
        lcd.setCursor(2,0);
        lcd.scrollDisplayLeft();
        delay(1000);
  }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Project is OFF");
        }
      if(feedcount==0){
    if(digitalRead(assembly)==1){
     double x= millis();
        lcd.clear();
        while(millis()-x<8000){
        lcd.setCursor(2,0);
        lcd.print("Nonmetal in Assembly    ");
        lcd.setCursor(2,1);
        lcd.print("Metal in feeding    ");
        lcd.setCursor(2,0);
        lcd.scrollDisplayLeft();
        delay(1000);
  }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Project is ON");
      }
    if(digitalRead(sort)==1){      
     double x= millis();
        lcd.clear();
        while(millis()-x<8000){
        lcd.setCursor(2,0);
        lcd.print("Nonmetal in Sorting    ");
        lcd.setCursor(2,1);
        lcd.print("Metal in feeding    ");
        lcd.setCursor(2,0);
        lcd.scrollDisplayLeft();
        delay(1000);
  }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Project is ON");
      }
        if(digitalRead(disassembly)==1){
     double x= millis();
        lcd.clear();
        while(millis()-x<5000){
        lcd.setCursor(2,0);
        lcd.print("Nonmetal in Disassembly    ");
        lcd.setCursor(2,1);
        lcd.print("Metal in feeding    ");
        lcd.setCursor(2,0);
        lcd.scrollDisplayLeft();
        delay(1000);
  }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Project is ON");
       // redunt=1;
      }
  }
  if(feedcount==1){
        if(digitalRead(assembly)==1){
     double x= millis();
        lcd.clear();
        while(millis()-x<8000){
        lcd.setCursor(2,0);
        lcd.print("Nonmetal in Feeding    ");
        lcd.setCursor(2,1);
        lcd.print("Metal in Assembly    ");
        lcd.setCursor(2,0);
        lcd.scrollDisplayLeft();
        delay(1000);
  }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Project is ON");
      }
    if(digitalRead(sort)==1){      
     double x= millis();
        lcd.clear();
        while(millis()-x<8000){
        lcd.setCursor(2,0);
        lcd.print("Nonmetal in Feeding    ");
        lcd.setCursor(2,1);
        lcd.print("Metal in Sorting    ");
        lcd.setCursor(2,0);
        lcd.scrollDisplayLeft();
        delay(1000);
  }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Project is ON");
      }
        if(digitalRead(disassembly)==1){
     double x= millis();
        lcd.clear();
        while(millis()-x<5000){
        lcd.setCursor(2,0);
        lcd.print("Nonmetal in Feeding    ");
        lcd.setCursor(2,1);
        lcd.print("Metal in Disassembly    ");
        lcd.setCursor(2,0);
        lcd.scrollDisplayLeft();
        delay(1000);
  }
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Project is ON");
        feedcount=0;
      }
    } 
  }
      
    }
    Serial.println("");
  }
}
