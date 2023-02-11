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

//OneButton button1(PinSW, true);


//defining some global Variables and setting the start/standart value

long position = 0;
const int readTimer = 1000;
float readTime = 0;
bool newRead = false;

byte fanspeed = 0;
int fanpercent = 0;
const int fanmin = 20;
float fantime = 0;
const int timer = 2500;
bool fanboost = false;
bool prevFanSpeed = 0;

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
bool modeFlag = true;

float tempC;
int fan = 10;

//crating function for the botscreen 
void initdysplay(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Starte System!");
  for (int i = 0; i < 16; i++)
  {
   lcd.setCursor(i,1);
   lcd.print("*");
   delay(150);
  }

}

void display(){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Temp:");
  lcd.setCursor(12,0);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("M:");

  lcd.setCursor(7,1); 
  lcd.print("Fan:");

}

void displayValue(){
  for (int i = 7; i < 12 ; i++)
  {
    lcd.setCursor(i,0);
    lcd.print(" ");
  }
  
  lcd.setCursor(7,0);
  lcd.print(tempC);

  if (modeFlag == true)
  {
    for (int i = 2; i < 7; i++)
    {
      lcd.setCursor(i,1);
      lcd.print(" ");
    }
    
    lcd.setCursor(2,1);
    lcd.print(mode);
    modeFlag = false;

  }
  

  for (int i = 11; i < 16 ; i++)
  {
    lcd.setCursor(i,1);
    lcd.print(" ");
  }

  lcd.setCursor(11,1); 
  lcd.print(fanpercent);
  lcd.print("%");
}


// creaing function for the menu
void displayMenu(){

  while (menuflag)  // loop depending on the menuflag, is running while true 
  {
    
    if (menuset == true)
    {
      lcd.clear();
      lcd.home();
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
    else if (position > 4)
    {
      menuestate = 4;
      myencod.write(16);
    }
        
    switch (menuestate)   // switching between the different menuoptions
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
      lcd.print(">IGLIDUR");
      
      if (digitalRead(PinSW)== LOW)
      {
        menueselect = 5;
      }      

      break;
    
    }

    delay(menudelay);


    Serial.print(menuflag);
    Serial.println(menueselect);

    switch (menueselect) // Settings depending on the selectet material and resetting some flags for the menue
    {
    case 1:
      mode = "PLA";
      mintemp = 20;
      maxtemp = 35;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;
      modeFlag = true;

      break;
    
    case 2:
      mode = "PETG";
      mintemp = 20;
      maxtemp = 40;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;
      modeFlag = true;

      break;

    case 3:
      mode = "FLEX";
      mintemp = 20;
      maxtemp = 45;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;
      modeFlag = true;
    
      break;

    case 4:
      mode = "PC";
      mintemp = 26;
      maxtemp = 55;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;
      modeFlag = true;

      break;

    case 5:
      mode = "IGLI";
      mintemp = 28;
      maxtemp = 50;
      menuflag = false;
      menueselect = 0;
      keypresstime = 0;
      modeFlag = true;

      break;

    default:
      break;

      
    
    }
  
  }
  keypresstime = 0;
  display();            // display the standard screen 
  displayValue();       // display the curent Values 
  
}




void readSensor(){
  
  sensors.requestTemperatures();            //getting the temperatuer from the sensor 

  tempC = sensors.getTempC(Thermometer);

  if (tempC >= mintemp && tempC <= maxtemp)   // map the speed of the fan depending on the Temp range of the material
  {
    fanspeed = map(tempC, mintemp, maxtemp, 0, 255);
  
  }
  else if (tempC > maxtemp)     // set te max speed of the fan if the Temp is over the max temp
  {
    fanspeed = 255;
  }
  else 
  {
    fanspeed = 0;
  }

  fanpercent = map(fanspeed, 0, 255, 0,100);  //map the speed to the % dutycicle 
  

  if (fanpercent < fanmin)          // the fan is not realy running if the dutycicle is less then 20%
  {
    fanspeed = 0;
    fanpercent = 0; 
  }

  if (fanpercent > 0 && prevFanSpeed == 0) //set a Flg to boost the Fan for a save startup wenn the fan was not running bevore
  {
    fanboost = true;
  }

  if (fanpercent >= 0 && fanpercent < fanmin)
  {
    prevFanSpeed = 0;
  }
  else
  {
    prevFanSpeed = 1;
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
  display();

}

void loop() {

  if (digitalRead(PinSW) == HIGH)  // query if the rotaryencoder is pressed to start the menu 
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
 case 1:              //going to the setup menu
   displayMenu();
   menuinit = 0;
   break;
 
 default:

 if (fanboost == true )   //wehn the Fanboost flag was set, here the fan runs for 2,5s at full speed, to get it reliable runns
 {
   fantime = millis();
   fanboost = false;

   while (millis() - fantime <= timer)
    {
      analogWrite(fan, 255);
    }
 }


 analogWrite(fan, fanspeed);  // write the normal fanspeed to the pin 
 displayValue();              // display the current values
 readSensor();                // get new temp values from the sensor
  break;

 }
  

}
