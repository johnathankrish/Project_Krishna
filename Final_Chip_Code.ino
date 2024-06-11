#include <TinyGPS++.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#include <TinyGPSPlus.h>
const int lebar=128;
const int tinggi=64;
const int reset=-1;
Adafruit_SSD1306 display(lebar,tinggi,&Wire,reset);
int state = 0;
const int pin1 = 1;
const int pin2= 0;
float gpslat=0.000,gpslon=0.000;

TinyGPSPlus gps;
SoftwareSerial sgps(6, 7);
SoftwareSerial sgsm(3, 2);

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT_PULLUP);
  sgsm.begin(9600);
  sgps.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  sgps.listen();
  while (sgps.available() > 0)
  {
    if(gps.encode(sgps.read()))
    {
    ///////////////////////////////////////////////
     display.clearDisplay();
     display.setTextSize(1.7);             
     display.setTextColor(WHITE);
     display.setCursor(0,10);           
     display.print(F("TIME: "));
     display.setCursor(30,10);
     int h=gps.time.hour()+5;
     int m=gps.time.minute()+30;
     if(m>59)
     {
      m=m-60;
      h=h+1;
     }
     if(h>23)
     {
      h=h-24;
     }
     display.print(h);
     display.setCursor(50,10);
     display.print(m);
     display.setCursor(70,10);
     display.print(gps.time.second());
     display.setCursor(0,40);      
     display.print(F("DATE: "));
     display.setCursor(30,40);
     display.print(gps.date.day());
     display.setCursor(50,40);
     display.print(gps.date.month());
     display.setCursor(70,40);
     display.print(gps.date.year());
     display.display();
     delay(10);
 
    //////////////////////////////////////////////
    if(gps.location.isUpdated())
    {
      gpslat=gps.location.lat();
      gpslon=gps.location.lng();
     /////////////////////////////////////////////
      int x=digitalRead(pin2);
      if (x == HIGH){
      Serial.println("Help Bot Turned ON ");
      sgsm.listen();
      sgsm.print("\r");
      delay(1000);
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      sgsm.print("AT+CMGS=\"+917708077528\"\r");
      delay(1000);
      sgsm.printf("Hey I need help,Give me a hand");
      sgsm.printf("\n");
      sgsm.print("https://maps.google.com/maps/?q=");
      sgsm.print(gpslat, 6);
      sgsm.print(",");
      sgsm.print(gpslon, 6);
      delay(1000);
      sgsm.write(26);
      delay(5000);
    }
    //////////////////////////////////////////////  
    if (digitalRead(pin1) == HIGH && state == 0 && x==LOW){
      Serial.println("Panic Mode !!!");
      sgsm.listen();
      sgsm.print("\r");
      sgsm.println("AT+CMGF=1\r");
      delay(1000);
      sgsm.print("AT+CMGS=\"+917708077528\"\r");
      delay(1000);
      sgsm.print("Hey I need help,Give me a hand");
      sgsm.print("\n");
      sgsm.print("https://maps.google.com/maps/?q=");
      sgsm.print(gpslat, 6);
      sgsm.print(",");
      sgsm.print(gpslon, 6);
      delay(1000);
      sgsm.write(26);
      state = 1;
    }
  if (digitalRead(pin1) == LOW){
      state = 0;
    }
    ///////////////////////////////////////////////
  }
 }
 }
}
/*Checking all the three module....*/
/*features
 * Modified Time
 * Gps sms
 * Bot
 * Final Model.
 */