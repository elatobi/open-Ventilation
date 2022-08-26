#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Encoder.h>
#include "OneButton.h"


LiquidCrystal_I2C lcd(0x27, 16,2);

#define ONE_WIRE_BUS 9  // Onewire Bus @ Pin 9

OneWire oneWire(ONE_WIRE_BUS);  //generating OneWire Bus 
DallasTemperature sensors(&oneWire); // Starting Temp Sensor
DeviceAddress Thermometer;    // creating Name of the themp sensor

Encoder myencod(2,4); // creating Encoder


//defining some global Variables and setting the start/standart value

long position = 0;

int fanspeed = 0;
int fanpercent = 0;

int maxtemp = 30;
int mintemp = 20;

const int PinSW = 3;    
byte prevKeyState = HIGH;
float keypresstime = 0;
int keytime = 3000;

int menuestate = 0;
int menueselect = 0;
bool menuflag = false;
int menudelay = 150;
bool menuset = false;
int menuinit = 0;

String mode = "PLA";

float tempC;
int fan = 10;

//crating function for the botscreen 
void initdysplay(){
  //lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Starte System!");
  for (int i = 0; i < 16; i++)
  {
   lcd.setCursor(i,1);
   lcd.print("*");
   delay(150);
  }

}

// creaing function for the menu

void displayMenu(){

  while (menuflag)  // loop depending on the menuflag, is running while true 
  {
    
    if (menuset == true)
    {
      
      lcd.home();
      lcd.clear();
      lcd.print("*****MENUE******"); 
      delay(2000);
      menuset = false;
      digitalWrite(PinSW, HIGH);
      menuflag = HIGH;
    }
    

        
    position = myencod.read()/4;  // read the postion of the encoder
    menuestate=position;
    
    
   
    if (position <= 0){   // checking if the encoder has value <0
      menuestate = 0;   // seting the menu variable to 0 for encoder postions <0
      myencod.write(0);    
    }
    else if (position > 5)
    {
      menuestate = 5;
      myencod.write(20);
    }
        
    switch (menuestate)   // 
    {      

    case 0:
      lcd.clear();
      lcd.home();
      lcd.print(">PLA");
      lcd.setCursor(1,1);
      lcd.print("PETG");
      if (digitalRead(PinSW)== LOW)
      {
        menueselect = 1;
      } 

      break;

    case 1:
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("PLA");
      lcd.setCursor(0,1);
      lcd.print(">PETG");
      if (digitalRead(PinSW)== LOW)
      {
        menueselect = 2;
      }      

      break;

    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(">FLEX");
      lcd.setCursor(1,1);
      lcd.print("PC");
      if (digitalRead(PinSW)== LOW)
      {
        menueselect = 3;
      }     

      break;

    case 3:
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("FLEX");
      lcd.setCursor(0,1);
      lcd.print(">PC");
      if (digitalRead(PinSW)== LOW)
      {
        menueselect = 4;
      }      

      break;

    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(">PA");
      lcd.setCursor(1,1);
      lcd.print("IGLIDUR");
      
      if (digitalRead(PinSW)== LOW)
      {
        menueselect = 5;
      }      

      break;

    case 5:
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("PA");
      lcd.setCursor(0,1);
      lcd.print(">IGLIDUR");
      
      if (digitalRead(PinSW)== LOW)
      {
        menueselect = 6;
      }      

      break;
    
    }

    delay(menudelay);


    switch (menueselect)
    {
    case 1:
      mode = "PLA";
      mintemp = 20;
      maxtemp = 30;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;

      break;
    
    case 2:
      mode = "PETG";
      mintemp = 20;
      maxtemp = 30;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;

      break;

    case 3:
      mode = "FLEX";
      mintemp = 20;
      maxtemp = 30;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;
    
      break;

    case 4:
      mode = "PC";
      mintemp = 26;
      maxtemp = 36;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;

      break;

    case 5:
      mode = "PA";
      mintemp = 28;
      maxtemp = 38;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;

      break;

    case 6:
      mode = "IGLI";
      mintemp = 28;
      maxtemp = 38;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;

      break;    

    default:
      break;

      
    
    }
  
  }
  keypresstime = 0;
  
}


void display(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Temp:");
  lcd.print(tempC);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(1,1);
  lcd.print(mode);

  lcd.setCursor(6,1); 
  lcd.print("Fan:");
  lcd.print(fanpercent);
  lcd.print("%");


}


void readSensor(){
  
  sensors.requestTemperatures();

  tempC = sensors.getTempC(Thermometer);

  if (tempC >= mintemp && tempC <= maxtemp)
  {
    fanspeed = map(tempC, mintemp, maxtemp, 0, 255);
  }
  else 
  {
    fanspeed = 0;
  }

  fanpercent = map(fanspeed, 0, 255, 0,100);

  if (fanpercent < 20){
    fanpercent = 0;
    fanpercent = 0;
  }

}

void setup() {

  Serial.begin(115200);

  pinMode(PinSW,INPUT_PULLUP);
 
  pinMode(fan, OUTPUT);
  
   
  sensors.begin();    
  sensors.getAddress(Thermometer, 0);

  lcd.init();
  lcd.backlight();
  initdysplay();
    

}

void loop() {

  if (digitalRead(PinSW) == HIGH)
 {
   prevKeyState = HIGH;
 }
 else
 {
   if (prevKeyState == HIGH)
   {
     keypresstime = millis();
     prevKeyState = LOW;
   }
   if ((millis()-keypresstime) >= keytime)
   {
     menuflag = true;
     menuset = true;
     menuinit = 1;
   }
 }

 switch (menuinit)
 {
 case 1:
   displayMenu();
   menuinit = 0;
   break;
 
 default:
 readSensor();
 analogWrite(fan, fanspeed);
 
 lcd.clear();
 display();

  break;
 }
  

}
