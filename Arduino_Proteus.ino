#include "DHT.h"
#include "DHT_U.h"
#define DHTTYPE DHT11 // DHT 11
#define DHTPIN 2 // what digital pin we're connected to
DHT dht(DHTPIN, DHTTYPE);

const int luz = A3;
const int luz2 = A4;
const int piezo1 = A0;
const int piezo2 = A1;
const int piezo3 = A2;
//#define luz A3
//#define piezo A0

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(luz, INPUT);
  pinMode(luz2, INPUT);
  pinMode(piezo1, INPUT);
  pinMode(piezo2, INPUT);
  pinMode(piezo3, INPUT);
}

void loop() {
  int l = analogRead(luz);
  int l2 = analogRead(luz2);
  int p1 = analogRead(piezo1);
  int p2 = analogRead(piezo2);
  int p3 = analogRead(piezo3);
  int p;
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (p1 == 0 && p2 == 0 && p3 == 0){
    p = 0;
  }
  if (p1 > 0 && p2 == 0 && p3 == 0){
    p = -10;
  }
  if (p1 == 0 && p2 > 0 && p3 == 0){
    p = 1;
  }
  if (p1 == 0 && p2 == 0 && p3 > 0){
    p = 10;
  }
  if (p1 > 0 && p2 > 0 && p3 == 0){
    p = -5;
  }
  if (p1 == 0 && p2 > 0 && p3 > 0){
    p = 5;
  }

  Serial.print(l);
  Serial.print(" ");
  Serial.print(l2);
  Serial.print(" ");
  Serial.print(p);
  Serial.print(" ");
  Serial.print(h);
  Serial.print(" ");
  Serial.println(t);

  delay(3000);
}
