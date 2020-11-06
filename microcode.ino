/* Arduino DS18B20 temp sensor tutorial
   More info: http://www.ardumotive.com/how-to-use-the-ds18b20-temperature-sensor-en.html
   Date: 19/6/2015 // www.ardumotive.com */


//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD



// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,16,2) for 16x2 LCD.

// Variables pour le modules HC SR-04: 
int trig = 8;// yellow wire
int echo = 9;// green wire
long lecture_echo;
long mesure = 0;
long m3 = 0;

//Variables pour module voltmetre:
int value = 0;
float R1 = 291000.0;
float R2 = 208700.0;
float voltage = 0;


// Mesure volume:
void mesureVolume(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo,HIGH);
  mesure = (((lecture_echo /58)-53)/18.2);
  m3 = (10-mesure);
}
void printVolume(){ 
  lcd.setCursor (0,0);
  lcd.print ("Vol: ");
  lcd.setCursor (5,0);
  lcd.print (m3);
  lcd.setCursor (7,0);
  lcd.print ("M3");
}

// Tension
void mesureTension(){
  value = analogRead(A0);
  voltage = value * (5.0/1024)*((R1 + R2)/R2);
}
void printTension(){
  lcd.setCursor (0,1);
  lcd.print ("U:");
  lcd.setCursor (3,1);
  lcd.print (voltage);
  lcd.setCursor (6,1);
  lcd.print ("V");
}
// Temperature
void printTemperatur(){
  lcd.setCursor(9, 1); // Set the cursor on the first column and first row.
  lcd.print("T:"); // Print the string "Temperature".
  lcd.setCursor(11, 1);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(15, 1);
  lcd.print("C");
}

void setup(void)
{
  Serial.begin(9600); //Begin serial communication
  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message
  sensors.begin();

    // Initiate the LCD:
  lcd.init();
  lcd.backlight();
}



void loop(void)
{ 
// Send the command to get temperatures
  sensors.requestTemperatures();  
  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  //Update value every 1 sec.
  delay(1000);

mesureVolume();
  
// The first line of the LCD:
printVolume();

// The second line of the LCD:  
  // Tension
printTension(); 
  // Temperature  
printTemperatur();
  
  
 
  
}
