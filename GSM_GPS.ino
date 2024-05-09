#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
int state = 0;
const int pin = 1;
float gpslat=0.000,gpslon=0.000;

TinyGPSPlus gps;
SoftwareSerial sgps(6, 7);
SoftwareSerial sgsm(3, 2);

void setup()
{
  pinMode(pin,INPUT);
  sgsm.begin(9600);
  sgps.begin(9600);
}

void loop()
{
  sgps.listen();
  while (sgps.available()>0)
  {
    gps.encode(sgps.read());
    if(gps.location.isUpdated())
    {
      gpslat=gps.location.lat();
      gpslon=gps.location.lng();
    if (digitalRead(pin) == HIGH && state == 0) {
      Serial.println("Pressed");
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
      Serial.println("Sms Sent");
    }
  if (digitalRead(pin) == LOW) {
      state = 0;
    }
  }
 }
}

// Finall Working Module...