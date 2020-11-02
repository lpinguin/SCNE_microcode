
/////////////
/* INCLUDES:*/
//#include <LiquidCrystal.h>


///////////////
/* VARIABLES:*/
LiquidCrystal lcd(12,11,5,4,3,2);

int trig = 8;// yellow
int echo = 9;// green
long lecture_echo;
long mesure=0;
long m3=0;


///////////////////////////////
/* PROTOTYPES & DECLARATIONS: */
   void infoHardware(){
   lcd.begin(20,4);
   lcd.setCursor(0,0);
   lcd.print ("Water tank level");
   lcd.setCursor(0,1);
   lcd.print ("Firmware v1.3");
   lcd.setCursor(0,2);
   lcd.print ("Hardware: prototype");
   lcd.setCursor(0,3);
   lcd.print ("Adrien DEWULF");
   delay (2000);
   lcd.clear();
}


void printResultat(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
   digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo,HIGH);
  mesure = (((lecture_echo /58)-53)/18.2);
  m3 = (10-mesure); 
  Serial.print("Volume en metre cube");
  Serial.println(m3);
  lcd.setCursor (0,0);
  lcd.print ("Volume en metre cube");
  lcd.setCursor (2,1);
  lcd.print (m3);
  lcd.setCursor (7,1);
  lcd.print ("M3");
  delay(500);
  lcd.clear();
}


////////////
/* SETUP: */

void setup(){

     pinMode(trig, OUTPUT);
     digitalWrite(trig, LOW);
     pinMode(echo, INPUT);
     Serial.begin(9600);
     Serial.println ("Adrien Dewulf");
}


///////////
/* LOOP: */

   void loop() {
   infoHardware();
   printResultat();

}
