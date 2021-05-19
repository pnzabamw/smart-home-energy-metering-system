#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <ThingSpeak.h>
//#define led 4
#define D2 2
#define led D2

char auth[]="dtsihcCnvOCd1ZrAhdhpFn0iwTBpuqcB";
char ssid[]="Nzapa";
char pass[]="012345678";
WiFiClient client;

#include "EmonLib.h"             // Including Emon Library
EnergyMonitor emon1;                  
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

unsigned long myChannelNumber=1386040;
const char*myWriteAPIkey= "TBAM369ZPB170VKM";
const char*server="api.thingspeak.com";
void updateThingSpeak(float I, float P ){
  ThingSpeak.setField(1,I);
  ThingSpeak.setField(2,P);
  ThingSpeak.writeFields(myChannelNumber,myWriteAPIkey);
}


void setup(){
 
    Serial.begin(9600);
    delay(1000);
    Blynk.begin(auth,ssid,pass);
    emon1.current(0,30); // Current calibration.
    emon1.voltage(2,250,2);// voltage

    WiFi.mode(WIFI_STA); 
    ThingSpeak.begin(client);
    //pinMode(buttonPin,INPUT);
    pinMode(led, OUTPUT);  
}

void loop()
{
  digitalWrite(led, HIGH);
  //delay(2000);
  //digitalWrite(led, LOW);
  
  
  double Irms = emon1.calcIrms(1480);  // Calculating current
  
  Serial.println("Current: ");
  Serial.print(Irms); // Irms
  Serial.println(" Amperes");
  Serial.println("Power: ");
  
  Serial.print(Irms*220); // Apparent power
  
  Serial.println("watts");
  Serial.println("*************");
  
  delay(2000);
  
  Blynk.run();

  WidgetLCD lcd(V0);
  const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

  Blynk.run(); 
  lcd.print(0,0,"Power: ");
  lcd.print(7, 0,Irms*220);
  lcd.print(12,0,"Watts");
  
  lcd.print(1,1,"Current: ");
  lcd.print(7, 1,Irms);
  lcd.print(12,1,"Amperes");
  if(client.connect(server,80))
  {
    updateThingSpeak(Irms,Irms*220);

}

}



  
