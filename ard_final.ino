#include "DHT.h"

#define pin_relay1L 2
#define pin_relay2H 7
#define pin_relay3M 8

#define DHTPIN 13
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);

int moistMin = 400;
int moistMax = 520;
int lightMin = 500;
int lightMax = lightMin + 400;
float minHum = 40;
float maxHum = 60;


void setup() {
  Serial.begin(9600);
  Serial.println(F("System started"));
  dht.begin();

  pinMode(pin_relay1L, OUTPUT);
  digitalWrite(pin_relay1L, LOW);
  pinMode(pin_relay2H, OUTPUT);
  digitalWrite(pin_relay2H, LOW);
  pinMode(pin_relay3M, OUTPUT);
  digitalWrite(pin_relay3M, LOW);
}

void loop() {

  delay(200);

  float temperature = getTemperature();
  float humidity = getHumidity();
  int lightlevel = 1023 - analogRead(A0);
  int moisthumidity = 1023 - analogRead(A1);

  if (humidity < minHum) {
  digitalWrite(pin_relay2H, HIGH);
  }
  if (humidity > maxHum) {
  digitalWrite(pin_relay2H, LOW);
  }


  if (lightlevel < lightMin) {
  digitalWrite(pin_relay1L, HIGH);
  delay(2000);  
  }
  if (lightlevel > lightMax) {
  digitalWrite(pin_relay1L, LOW);
  }


  if (moisthumidity < moistMin) {
  digitalWrite(pin_relay3M, HIGH);
  delay(1000);
  digitalWrite(pin_relay3M, LOW);
  delay(10000);
  }
  if (moisthumidity > moistMax) {
  digitalWrite(pin_relay3M, LOW);
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C "));
  Serial.print(lightlevel);
  Serial.print(F(" "));
  Serial.println(moisthumidity);
}


float getTemperature() {

  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  return t;
}


float getHumidity() {

  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  return h;

}