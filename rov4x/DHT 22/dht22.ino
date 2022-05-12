#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN  6       // indique la pin
#define DHTTYPE DHT22   // indique le DHT

DHT dht(DHTPIN, DHTTYPE);
 
void setup()
{
  Serial.begin(9600); // fréquence de transmission de bit
  dht.begin(); // initisalisation du capteur
}
 
void trame(int h,float t)
{
  Serial.print('$');
  Serial.print(1);
  Serial.print('-');
  Serial.print(t); // affiche la température
  Serial.print('-');
  Serial.print(h); // affiche le taux d'humidité
  Serial.print('.');
  Serial.println(); 
}
 
void loop()
{
  delay(2000); // temporisation de 2 sec
  int h = dht.readHumidity(); // associe h à l'humidité
  float t = dht.readTemperature(); // associe t à la température

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  trame(h,t); 
}
