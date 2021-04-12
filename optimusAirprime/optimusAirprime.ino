#include <SparkFun_SGP30_Arduino_Library.h>
#include <LiquidCrystal.h>
#include <Wire.h>   
#define red 6
#define green 9                          
 
SGP30 sgp;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
    
void setup() {
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  lcd.begin(16, 2);
  Wire.begin();
  if (sgp.begin() == false) {
    lcd.print("No SGP30 Detected.");
    while (1);
  }
  sgp.initAirQuality();
    
}
 
void loop() 
{
  sgp.measureAirQuality();
  if (sgp.CO2 >= 250 && sgp.CO2 <= 1000)
  {
     digitalWrite(green, HIGH) ;
     digitalWrite(red, LOW);
  }
  if (sgp.TVOC >= 0 && sgp.TVOC <= 250)
  {
    digitalWrite(green, HIGH) ;
    digitalWrite(red, LOW);
  }
  else if(sgp.CO2 > 1000)
  {
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
  else if (sgp.TVOC > 250)
  {
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
  lcd.setCursor(0, 0);                      
  lcd.print("TVOC: ");
  lcd.print(sgp.TVOC);                          
  lcd.print(" ppb");
  lcd.setCursor(0, 1);
  lcd.print("CO2: ");
  lcd.print(sgp.CO2);
  lcd.print(" ppm ");
  delay(3000);
  lcd.clear();
  sgp.measureRawSignals();
  lcd.setCursor(0, 0);                      
  lcd.print("Raw H2: ");
  lcd.print(sgp.H2);                    
  lcd.setCursor(0, 1);
  lcd.print("Raw Ethanol: ");
  lcd.print(sgp.ethanol);
  delay(3000);
  lcd.clear();
  
}
  
