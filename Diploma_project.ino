#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <LiquidCrystal.h>
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(4, 6,10, 11, 12, 13);

Servo myservo;

unsigned long prevMillis=0;
long interval = 60000; //32400000 millisecond = 9 hours
long countdown1 = 60000;
long countdown2 = 0;

int pos = 0;

void setup(void)
{
  lcd.begin(16, 2);
  myservo.attach(9);
  // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}
void loop(void)
{ 
TempSensor();

unsigned long currentMillis = millis();

  if((unsigned long)(currentMillis - prevMillis >= interval)){
    Serial.println("Watering...............................");
    lcd.setCursor(0, 0);
    lcd.print("Watering.........");
    lcd.print(".................");
    prevMillis = currentMillis;
    }
}
void TempSensor(){  
  int sensorSoilMoistureValue=analogRead(A3);
  int lowestmoisture=1000;

  Serial.print("Requesting sensors...");
  sensors.requestTemperatures();
 // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  // Send the command to get temperatures
  int sensorTempValue=sensors.getTempCByIndex(0);

  Serial.println("DONE");
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(sensorTempValue);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Soil Mois: ");
  lcd.print(sensorSoilMoistureValue);
  Serial.print("Soil Moisture: ");
  Serial.println(sensorSoilMoistureValue);
  Serial.print("Temp: ");
  Serial.print(sensorTempValue);  //print the temperature on serial monitor
  Serial.println(" C");

  if(sensorSoilMoistureValue > lowestmoisture){

      interval = interval - 60000;
    
      unsigned long currentMillis = millis();

      if((unsigned long)(currentMillis - prevMillis >= countdown1)){   
      Serial.println("Water ME!!!!!!!!!!!!!!!!!!!!!!!!!");
      lcd.setCursor(0, 0);
      lcd.print("Water ME.........");
      lcd.print(".................");
      prevMillis = currentMillis;
      interval = 60000;
      }
    }

   if(sensorTempValue > 36){

      interval = interval - 20000;
    
      unsigned long currentMillis = millis();

      if((unsigned long)(currentMillis - prevMillis >= countdown2)){
      Serial.println("Water ME!!!!!!!!!!!!!!!!!!!!!!!!!");
      lcd.setCursor(0, 0);
      lcd.print("Water ME.........");
      lcd.print(".................");
      prevMillis = currentMillis;
      interval = 60000;
      }
    }
  
  }
