int relay_1 = 5;
#define Sensor 7
#define LED 4
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();                    
  lcd.backlight();
  Serial.begin(9600);
  pinMode(Sensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(relay_1, OUTPUT);

}

void loop() {
  bool value = digitalRead(Sensor);
  Serial.println(value);

  if (value == 0) {
    lcd.clear(); 
    digitalWrite(LED, HIGH);
    lcd.setCursor(1,0);
    lcd.print("Fire Fire");
    delay(250);
    digitalWrite(relay_1, HIGH);
    delay(1000);
    digitalWrite(relay_1, LOW);
    delay(1000);
  } 
    else {
    lcd.clear();
    digitalWrite(LED, LOW);
    lcd.setCursor(2,0);
    lcd.print("No Fire");
    delay(250);
  }
}
