// Checkpoint02

#include<LiquidCrystal.h> // biblioteca do lcd

LiquidCrystal lcd(7,6,5,4,3,2); // RS, E, D4, D5, D6, D7

int ledVermelho = 11;
int ledAmarelo = 12;
int ledVerde = 13;
int buzzer = 10;
int sensorLDR = A5;
int sensorTMP = A4;
int limiteLDR = 600;

double tensao = 0; //declarando as variaveis
double temp = 0;

void setup()
{
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorLDR, INPUT);
  pinMode(sensorTMP, INPUT);
  
  Serial.begin(9600);
  lcd.begin(16,2); 
   
}

void loop(){
  
  int sensorUmidade = analogRead(A3);
  int umidade = (map(sensorUmidade, 0, 1023, 10, 70));
  int leituraL = analogRead(sensorLDR);
  int leituraT = analogRead(sensorTMP);
  tensao = (leituraT / 1023.0) * 5000; // calculo pra simular o sensor dht
  temp = (tensao - 500) * 0.1;
  
  Serial.print("\t Umidade: "); //valores de umidade no monitor
  Serial.print(map(sensorUmidade, 0, 1023, 10, 70));
  Serial.println("%");
  
  Serial.print("\t Temperatura = "); //valores de temperatura no monitor
  Serial.print(temp,1);

  if (leituraL > limiteLDR) {
    lcd.clear();
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(buzzer, LOW);    
   
  }  
  else if (leituraL >= 125) {
    lcd.clear();
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW);
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0,0);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0,1);
    lcd.print("luz");
    delay(5000);
      
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
    delay(5000);
  }    
  if ((temp >= 10) && (temp <= 15)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temperatura OK");
      lcd.setCursor(0,1);
	  lcd.print("Temp. = ");
	  lcd.print(temp, 1);
      lcd.print("C");
      delay(5000);
  }
  else if (temp > 15){
    lcd.clear();
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(buzzer, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Temp. ALTA ");
    lcd.setCursor(0,1);
    lcd.print("Temp. = ");
    lcd.print(temp, 1);
    lcd.print("C");
    delay(5000);
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
    delay(5000);
  }
  
  if ((umidade >= 60) && (umidade <= 80)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umidade OK ");
    lcd.setCursor(0,1);
	lcd.print("Umidade = ");
	lcd.print(umidade, 1);
    lcd.print("%");
    delay(5000);
  }
  else if (umidade <= 50){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umidade BAIXA ");
    lcd.setCursor(0,1);
	lcd.print("Umidade = ");
	lcd.print(umidade, 1);
    lcd.print("%");
    delay(5000);
  }
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Umidade ALTA ");
    lcd.setCursor(0,1);
	lcd.print("Umidade = ");
	lcd.print(umidade, 1);
    lcd.print("%");
    delay(5000);
  } 
}