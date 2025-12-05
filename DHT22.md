# Sensor DHT22

O sensor DHT22 é utilizado para medir temperatura e umidade relativa do ar através de comunicação digital.

<img width="499" height="354" alt="image" src="https://github.com/user-attachments/assets/6fd6fc1a-1098-471d-b392-03a16d050f2f" />


# Dados Técnicos do Sensor DHT22

| Característica        | Descrição                              |
|-----------------------|----------------------------------------|
| Tipo                  | Sensor digital de temperatura e umidade |
| Tensão de Operação    | 3.3V a 5.5V                           |
| Corrente de Operação  | 0.5mA a 2.5mA                         |
| Faixa de Temperatura  | 0°C a 100°C                            |
| Precisão Temperatura  | ±2°C                                  |
| Faixa de Umidade      | 0% a 100%                             |
| Precisão Umidade      | ±5%                                   |
| Tempo de Resposta     | 2 segundos                            |
| Interface             | 1-Wire (protocolo proprietário)       |


## Exemplo de Código

Segue um exemplo de código para leitura de dados do DHT22 usando Arduino:

```cpp
#include <DHT.h> // Biblioteca Necessária

// Definir o pino do sensor e o tipo
#define DHTPIN 4 // Pino de dados conectado ao pino digital 4
#define DHTTYPE DHT22 // Definir o modelo do sensor (DHT22)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando leitura do DHT22");
  dht.begin();
  
  // Aguardar estabilização
  delay(2000);
}

void loop() {
  // Ler temperatura e umidade
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  
  // Verificar se as leituras são válidas
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha ao ler os dados do sensor!");
    delay(2000);
    return;
  }
  
  // Calcular índice de calor (sensação térmica)
  float indiceCalor = dht.computeHeatIndex(temperatura, umidade, false);

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");
  
  Serial.print("Sensação Térmica: ");
  Serial.print(indiceCalor);
  Serial.println(" °C");
  
  // Classificação do ambiente
  if (temperatura < 18) {
    Serial.println("Ambiente: FRIO");
  } else if (temperatura > 30) {
    Serial.println("Ambiente: QUENTE");
  } else {
    Serial.println("Ambiente: AGRADÁVEL");
  }
  
  if (umidade < 40) {
    Serial.println("Umidade do Ar: BAIXA");
  } else if (umidade > 70) {
    Serial.println("Umidade do Ar: ALTA");
  } else {
    Serial.println("Umidade do Ar: IDEAL");
  }
  
  Serial.println("------------------------");
  
  delay(2000); // Intervalo de 2 segundos entre leituras
}
```


## Aplicações no Sistema de Irrigação

- **Monitoramento Ambiental**: Acompanhar condições climáticas em tempo real
  
