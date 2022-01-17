#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int rs = 12, en = 11, d4 = 5,
d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int base = 9;

void setup() {
    lcd.begin(16, 2);
    pinMode(base, OUTPUT);
    lcd.print("Humedad:");
    Serial.println("DHTxx test!");
    dht.begin();
    Serial.begin(9600);
}

void loop() {
    delay(1000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
}

float hif = dht.computeHeatIndex(f, h);
float hic = dht.computeHeatIndex(t, h, false);

Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" *C ");
Serial.print(f);
Serial.print(" *F\t");
Serial.print("Heat index: ");
Serial.print(hic);
Serial.print(" *C ");
Serial.print(hif);
Serial.println(" *F");

if(h<30)
{digitalWrite(base,HIGH);
lcd.setCursor(0, 0);
lcd.print("Agua pls");
lcd.setCursor(0, 1);
lcd.print(h);}
else
{digitalWrite(base,LOW);
lcd.setCursor(0,0);
lcd.print("Humedad:");
    lcd.setCursor(0, 1);
lcd.print(h);}
}