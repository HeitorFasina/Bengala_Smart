// TCC Desenvlvimento de Sistemas: Bengala inteligente
//
// Integrantes: Heitor Fasina
//              Kauan Hiroshi obrata
//              Murilo Ferreira Martins
//              Nicholas Lopes de Almeida 
//              Pedro Henrique de Lima Fávaro

// Carrega biblioteca do sensor ultrassonico
#include <Ultrasonic.h> 

// Define os pinos para o trigger e echo, respectivamente
#define pinTrigger 8
#define pinEcho 7

// Define o pino para o módulo Buzzer
#define buzzer 2

// Define a variável "distancia"
long distancia;

// Inicializa e nomeia o sensor nos pinos definidos
Ultrasonic sensorUltrassonico(pinTrigger, pinEcho);


void setup() {
  // Define o buzzer como saída
  pinMode(buzzer, OUTPUT);

  // Habilita Comunicação Serial a uma taxa de 9600 bauds
  Serial.begin(9600);
}


void loop() {
  // Lê e retorna as informações de distancia do sensor em CM
  distancia = sensorUltrassonico.Ranging(CM); 

  // Imprime o valor da variável distancia no serial motor
  Serial.print(distancia);
  Serial.println("cm");

  
  if (distancia <= 20) {
    tone(buzzer, 440);
  } else {
    noTone(buzzer);
  }
  
  delay(100);
}
