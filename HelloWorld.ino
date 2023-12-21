#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <LED.h>
#include "Relay.h"
#include "Pitch.h"


Relay light(6, false);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// change this to make the song slower or faster
int tempo = 110;

// change this to whichever pin you want to use
int buzzer = 11;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {
  
  // Prince Igor - Polovtsian Dances, Borodin 
  NOTE_G4, 4, NOTE_G4, 4, NOTE_D5, -2,
  NOTE_C5, 8, NOTE_D5, 8, NOTE_AS4, 4, NOTE_A4, 8, NOTE_G4, 8,
  NOTE_A4, 8, NOTE_AS4, 8, NOTE_C5, 1,
  
  NOTE_D5, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 8,
  NOTE_D4, 4, NOTE_D4, 4, NOTE_G4, -2,
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 8, NOTE_E4, 8,
  
  NOTE_F4, 4, NOTE_E4, 4, NOTE_D4, 1,
  NOTE_E4, 4, NOTE_F4, 4, NOTE_A4, 4,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_AS4, -2,

  NOTE_C5, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_AS4, 4, NOTE_C5, -2,
  NOTE_CS5, 4, NOTE_C5, 4, NOTE_A4, 4,
  
  NOTE_CS5, 4, NOTE_CS4, 4, NOTE_F5, -2,
  NOTE_G5, 4, NOTE_F5, 4, NOTE_DS4, 8, NOTE_CS4, 8,
  NOTE_F5, 2, NOTE_C5, -2, 
  
  NOTE_AS4, 4, NOTE_C5, 4, NOTE_AS4, 8, NOTE_A4, 8,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_AS4, 1,
  NOTE_C5, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_G4, 8,  

  NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 1,
  NOTE_AS4, 4, NOTE_A4, 4, NOTE_F4, 4,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_D5, -2,

  NOTE_C5, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_G4, 8,
  NOTE_A4,-1, NOTE_A4,-1, REST,2,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_D5, -2,
  
  NOTE_C5, 8, NOTE_D5, 8, NOTE_AS4, 4, NOTE_A4, 8, NOTE_G4, 8,
  NOTE_A4, 8, NOTE_AS4, 8, NOTE_C5, 1,
  NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 4, NOTE_AS4, 8, NOTE_A4, 8,
  
  
  NOTE_D4, 4, NOTE_D4, 4, NOTE_G4, -2,
  NOTE_G4, 8, NOTE_A4, 8, NOTE_G4, 4, NOTE_F4, 8, NOTE_E4, 8,
  NOTE_F4, 8, NOTE_E4, 8, NOTE_D4, -2,//1
  
  REST,4, NOTE_C5, 8, NOTE_D5, 8, NOTE_C5, 4, NOTE_AS4, 8, NOTE_A4, 8,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_B4, -2,
  NOTE_C5, 4, NOTE_AS4, 4, NOTE_A4, 8, NOTE_G4, 8,  

  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, -1, REST,4,
  NOTE_G4, 4, NOTE_G4, 4, NOTE_D5, -2,
  NOTE_C5, 8, NOTE_D5, 8, NOTE_AS4, 4, NOTE_A4, 8, NOTE_G4, 8,
  
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, -2,
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, -2,
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, -1,

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setup()
{
  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);

  LED led(5);
  LED led2(4);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  light.begin();
  led.begin(1000);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("FIRE FIRE");
  lcd.setCursor(1,0);
  lcd.print("DEAD");
}
}

void loop(){

  light.turnOff(); //turns relay off
  light.turnOn();  //turns relay on
  bool isLightOn = light.getState(); //returns a bool, true = on, false = off  

  


  
   digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
   digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
