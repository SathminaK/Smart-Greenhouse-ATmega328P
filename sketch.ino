#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define SOIL_PIN A0
#define PUMPLED 13
#define SERVOPIN 9

const float TEMP_THRESHOLD = 30.0;
const int SOIL_THRESHOLD = 400;

DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
Servo windowServo;


void setup(){
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  windowServo.attach(SERVOPIN);

  pinMode(PUMPLED, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("SMART GREENHOUSE");
  lcd.setCursor(0,1);
  lcd.print("System Initialized");
  delay(2000);
  lcd.clear();
}

void loop(){

float temp = dht.readTemperature();
float hum = dht.readHumidity();

int soilMoisture = analogRead(SOIL_PIN);

if (isnan(temp) || isnan(hum)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

if (temp>TEMP_THRESHOLD){
  windowServo.write(90);
  Serial.println("Alert: High Temp! Opening Window.");
}
else{
  windowServo.write(0);
}
if (soilMoisture < SOIL_THRESHOLD) {
    digitalWrite(PUMPLED, HIGH); 
    Serial.println("Alert: Dry Soil! Activating Pump.");
  } else {
    digitalWrite(PUMPLED, LOW);   

  }

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Temp: ");
lcd.print(temp, 1);
lcd.print(" C");

lcd.setCursor(0, 1);              
lcd.print("Hum:  "); 
lcd.print(hum, 1);                 
lcd.print(" %");
delay(3000);

lcd.clear();                     
lcd.setCursor(0, 0);              
lcd.print("Soil Moisture:");
lcd.setCursor(0, 1);              
lcd.print("Value: "); 
lcd.print(soilMoisture);         
delay(3000);                       
}






