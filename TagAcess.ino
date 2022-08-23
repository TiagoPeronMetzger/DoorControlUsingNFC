// Libraries
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

// Create the NFC object
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

String savedTagId = "2C 0B 5A 32"; // Main Tag ID
String tagId = "None";

const int correctTagPin = 4; // sets a PIN for the correct tag LED
const int incorrectTagPin = 5; // sets a PIN for the incorrect tag LED

// Create the lcd object
LiquidCrystal_I2C lcd(0x27, 16,2);  //

 
void setup(void) 
{
  Serial.begin(115200);
  Serial.println("System initialized");
  
  
  nfc.begin();
  lcd.begin ();
  lcd.backlight();// Turn on the backlight on LCD. 
  
  pinMode(correctTagPin, OUTPUT);
  pinMode(incorrectTagPin, OUTPUT);
}
 
void loop() 
{
  
  readNFC();
}

/*
 * @Brief: Checks for a tag and if the ID is equal to
 * the saved tag ID, then lights up the correct LED pin,
 * otherwise, lights the incorrect led pin.
 */
void readNFC() 
{
 // Detected a Tag
 if (nfc.tagPresent())
 {
   NfcTag tag = nfc.read();
   tag.print();
   tagId = tag.getUidString();
   if (tagId == savedTagId)
   {
     lcd. clear();
     lcd. setCursor (0, 0);
     lcd. print ( "Porta liberada" );
     lcd. setCursor (0, 1);
     lcd. print ( "ID:" );
     lcd. print (tagId);

     // light up the LEDs
     digitalWrite(correctTagPin, HIGH);
     digitalWrite(incorrectTagPin, LOW);
   }
   else
   {
     lcd. clear();
     lcd. setCursor (0, 0);
     lcd. print ( "Tag Invalida" );
     
     // light up the LEDs
     digitalWrite(correctTagPin, LOW);
     digitalWrite(incorrectTagPin, HIGH);
   }
 }
 // Didn't detected a tag
 else
 {
   lcd. clear();
   lcd. setCursor (0, 0);
   lcd. print ( "Nenhuma Tag" );
   lcd. setCursor (0, 1);
   lcd. print ( "Foi Encontrada" );
   
   // light down the LEDs
   digitalWrite(correctTagPin, LOW);
   digitalWrite(incorrectTagPin, LOW);
 }
 delay(1000);
}
