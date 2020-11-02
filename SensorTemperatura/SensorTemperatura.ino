#include <Wire.h>
#include <ClosedCube_HDC1080.h>

ClosedCube_HDC1080 hdc1080; //Objeto Sensor de Temperatura

// Paramentos para a função de filtro
int const TempoParada= 4000; // 4000 = 4 segundos
int const passo= 50; // 50 milissegundos para cada medição
/////////////////////////////////////

// Pinagem
int const pinLedVermelho= 10;
int const pinLedVerde= 9;
int const pinBotao= 8;
//////////

void setup() {
  hdc1080.begin(0x40);
  pinMode(pinLedVermelho, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);
}

void loop() {
  if(!digitalRead(pinBotao)) /* botão precionado, ativa a leitura da temperatura*/
    alertaTemperatura(filtro());
}

/*
 * Verifica se a temperatura ultrapassa o limite de 37.5 C°
*/
void alertaTemperatura(float temp){
  
  if(temp > 37.5){
    digitalWrite(pinLedVermelho, HIGH);
    digitalWrite(pinLedVerde, LOW);
  }
  else{
    digitalWrite(pinLedVermelho, LOW);
    digitalWrite(pinLedVerde, HIGH);
  }

  delay(2000);
  
  digitalWrite(pinLedVermelho, LOW);
  digitalWrite(pinLedVerde, LOW);
  
  return;
}

/*
 * Faz uma media simples dos valores medidos do sensor, aumenta a precisão do sensor
 */

float filtro(void){
  long int tempoInicial = millis();
  long int cont= 0;
  double valorSensor= 0;
  
  while(millis() - tempoInicial <= TempoParada){
    valorSensor= hdc1080.readTemperature();
    cont++;
    delay(passo);
  }

  return valorSensor/cont;
}
