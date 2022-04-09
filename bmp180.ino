#include <SFE_BMP180.h>
#include <Wire.h>
 
SFE_BMP180 sensor; 
double tabanBasinci = 0, irtifa = 0, maxIrtifa = 0; 

void setup() 
{   
  Serial.begin(9600);
   
  if (!sensor.begin())  
  {
    Serial.println("BMP180 Pressure Sensor Error!"); 
    while(1);  
  }
  tabanBasinci = getPressure(); 
} 
   
void loop() 
{   
  irtifa = irtifaHesapla();

  if (irtifa > maxIrtifa) 
    maxIrtifa = irtifa; 
    
  Serial.println("Anlik Irtifa: " + String(irtifa) + ", Olculen Maksimum Irtifa: " + String(maxIrtifa));

  delay(50); 
}
  
double getPressure() 
{
  char status= ' '; 
  double sicaklik = 0, basinc = 0;
    
  status = sensor.startTemperature(); 
  if (status != 0)
  {
    delay(status); 
    status = sensor.getTemperature(sicaklik);  
    status = sensor.startPressure(3); 

    if (status != 0) 
    {
      delay(status);
      status = sensor.getPressure(basinc, sicaklik);
  
      if (status != 0)
            return basinc;
    }  
  }
}

double irtifaHesapla()
{
  return sensor.altitude(getPressure(), tabanBasinci); 
}
