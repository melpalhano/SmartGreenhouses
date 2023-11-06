#include <DHT.h>
#include <Stepper.h>

const int DHTPIN = A0;
const int DHTTYPE = DHT11;
const int buzzerPin = 3;
const int ledPin = 13;
const int e1 = 8;
const int e2 = 9;
const int e3 = 10;
const int e4 = 11;
const int passos = 64;
float temperatura = 0;

Stepper mp(passos, e1, e3, e2, e4);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  mp.setSpeed(500);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

float lerTemperatura() {
  float temperature = dht.readTemperature();
  return temperature;
}

void controlarBuzzerELED() {
delay(250); 
temperatura = lerTemperatura(); 
 if (temperatura > 28.0) {
    tone(buzzerPin, 200);
    digitalWrite(ledPin, HIGH);
  } else {
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
  }
}

void controlarMotor(float temperatura) {
  if (temperatura > 27.0) {
    for (int i = 0; i < passos; i++){
      mp.step(passos);
    }
  } else {
    mp.step(0);
  }
}

void loop() {
  controlarBuzzerELED();
  controlarMotor(temperatura);
  Serial.print("Temperature (C): ");
  Serial.println(temperatura);
}
