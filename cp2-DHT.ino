#include "DHT.h"
#include<LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int ledVermelho = 11;
int ledAmarelo = 12;
int ledVerde = 13;
int buzzer = 10;
int sensorLDR = A5;
const int sensorDHT = A4;
int limiteLDR = 600;

DHT dht(A4, DHT11);
int temp = 0;
int umid = 0;
int numLeituras = 0;
float mediaTemp = 0;
float mediaUmid = 0;

void setup() {
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorLDR, INPUT);
  pinMode(sensorDHT, INPUT);

  Serial.begin(9600);
  delay(1000);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  temp = dht.readTemperature();
  umid = dht.readHumidity();

  mediaTemp += temp;
  mediaUmid += umid;
  numLeituras++;

  mediaTemp /= numLeituras;
  mediaUmid /= numLeituras;

  Serial.print("Temperatura média: ");
  Serial.print(temp);
  Serial.println(" *C");
  Serial.print("Umidade média: ");
  Serial.print(umid);
  Serial.println("%");

  if (numLeituras >= 1000) {
    numLeituras = 0;
    mediaTemp = 0;
    mediaUmid = 0;
  }
  Serial.println(sensorLDR);
  Serial.print("Umidade: ");
  Serial.print(umid);
  Serial.print("%");
  Serial.print(" / Temperatura: ");
  Serial.print(temp);
  Serial.println("*C");

  int leituraL = analogRead(sensorLDR);

  if (leituraL > limiteLDR) {
    lcd.clear();
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(buzzer, LOW);
  }
  else if (leituraL >= 5) {
    lcd.clear();
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0,0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0,1);
    lcd.print("luz");
    delay(1000);
      
  }
  else {
    lcd.clear();
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(buzzer, HIGH); // liga o buzzer
    lcd.setCursor(0,0);
    lcd.print("Ambiente Muito");
    lcd.setCursor(0,1);
    lcd.print("CLARO ");
    delay(1000);
  }    
  if ((temp >= 10) && (temp <= 25)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperatura OK");
    lcd.setCursor(0,1);
    lcd.print("Temp. = ");
    lcd.print(temp, 1);
    lcd.print("C");
    delay(1000);
  }
  else if (temp > 26){
    lcd.clear();
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Temp. ALTA ");
    lcd.setCursor(0,1);
    lcd.print("Temp. = ");
    lcd.print(temp, 1);
    lcd.print("C");
    delay(1000);
  }
  else{
    lcd.clear();
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Temp. BAIXA ");
    lcd.setCursor(0,1);
    lcd.print("Temp. = ");
    lcd.print(temp, 1);
    lcd.print("C");
    delay(1000);
  }
  
  if ((umid >= 60) && (umid <= 80)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umidade OK ");
    lcd.setCursor(0,1);
    lcd.print("Umidade = ");
    lcd.print(umid, 1);
    lcd.print("%");
    delay(1000);
  }
  else if (umid <= 59){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umidade BAIXA ");
    lcd.setCursor(0,1);
    lcd.print("Umidade = ");
    lcd.print(umid, 1);
    lcd.print("%");
    delay(1000);
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umidade ALTA ");
    lcd.setCursor(0,1);
    lcd.print("Umidade = ");
    lcd.print(umid, 1);
    lcd.print("%");
    delay(1000);
  } 
}
