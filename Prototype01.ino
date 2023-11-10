#include <DHT.h>
#include <Stepper.h>

//declaração dos pinos conectados
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

//Contagem de passos do motor
Stepper mp(passos, e1, e3, e2, e4);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  //Inicializa a comunicação serial
  Serial.begin(9600);
  //Inicializa o sensor DHT11
  dht.begin();
  //Declara a velocidade do motor de passo
  mp.setSpeed(500);
  // Define o pino do buzzer como saída
  pinMode(buzzerPin, OUTPUT);
  // Define o pino do led como saída
  pinMode(ledPin, OUTPUT);
}

//Faz o DHT11 ler a temperatura
float lerTemperatura() {
  float temperature = dht.readTemperature();
  return temperature;
}

//Função de controle do led e do buzzer
void controlarBuzzerELED() {
delay(250); 
// Verifica se a temperatura é maior que 28 graus
temperatura = lerTemperatura(); 
 if (temperatura > 28.0) {
    tone(buzzerPin, 200); // liga o buzzer
    digitalWrite(ledPin, HIGH); // Acende o LED
  } else {
    noTone(buzzerPin);// desliga o buzzer
    digitalWrite(ledPin, LOW); // apaga o LED
  }
}

//Função de controle do motor
void controlarMotor(float temperatura) {
// Verifica se a temperatura é maior que 27 graus
  if (temperatura > 27.0) {
    for (int i = 0; i < passos; i++){
      mp.step(passos);// liga o motor
    }
  } else {
    mp.step(0);// desliga o motor
  }
}

//chama as funções do motor, do buzzer e do led
void loop() {
  controlarBuzzerELED();
  controlarMotor(temperatura);
  Serial.print("Temperature (C): ");
  Serial.println(temperatura); //imprime a temperatura no monitor serial
}
