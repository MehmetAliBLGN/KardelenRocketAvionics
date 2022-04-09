#include <TinyGPS++.h>

TinyGPSPlus gps; 
const int gpsBaud = 9600;

void setup() 
{
  Serial1.begin(gpsBaud);
}

void loop() 
{
  String loraVeri = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6) + ";"; 

  Serial.println("Uydu Sayisi: " + String(gps.satellites.value()) + " Enlem: " + 
    String(gps.location.lat(), 6) + " Boylam: " + String(gps.location.lng(), 6));

  smartDelay(150);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());

  } while (millis() - start < ms);
}
