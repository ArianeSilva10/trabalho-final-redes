#include <ESP8266WiFi.h>
#include "DHT.h"
#define LED_PINO_FRIO 5  // gpio 5, d1, azul
#define LED_PINO_ALERTA 16  // D0, VERDE
#define LED_PINO_QUENTE 4  // D2, VERMELHO
#define DHT11_SINAL 2  // gpio 2, pino D4
#define DHT_TIPO DHT11  // tipo do meu sensor
#define TOKEN "KSHA627ESP"
DHT dht11(DHT11_SINAL, DHT_TIPO);


// ctgqx-177-37-186-190.a.free.pinggy.link:42935

const char* rede = "ariane5055xda";
const char* senha = "A2025*ufc";
const char* ip = "ctgqx-177-37-186-190.a.free.pinggy.link";
const int porta = 42935;

void setup() {
  pinMode(LED_PINO_ALERTA, OUTPUT);
  pinMode(LED_PINO_QUENTE, OUTPUT);
  pinMode(LED_PINO_FRIO, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(rede, senha);
  dht11.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("conectando ao wifi...");
  }

  Serial.println("conectado");
}

void loop() {
  float temperatura = dht11.readTemperature();
  float umidade = dht11.readHumidity();
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("falha na leitura do dht11");
  } else {
    WiFiClient cliente;
    if (cliente.connect(ip, porta)) {
      String msg = "token:" TOKEN ";temperatura:" + String(temperatura) +
                   ";umidade:" + String(umidade);
      cliente.println(msg);
      // aguardando o comando do servidor
      long time_out = millis() + 3000;
      while (!cliente.available() && millis() < time_out)
      {};
      if (cliente.available()) {
        String comando = cliente.readStringUntil('\n');
        comando.trim();
        if (comando == "TEMPERATURA_QUENTE") {
          digitalWrite(LED_PINO_QUENTE, HIGH);
          digitalWrite(LED_PINO_ALERTA, LOW);
          digitalWrite(LED_PINO_FRIO, LOW);

          Serial.println("led vermelho");
        } else if (comando == "TEMPERATURA_ALERTA") {
          digitalWrite(LED_PINO_ALERTA, HIGH);
          digitalWrite(LED_PINO_FRIO, LOW);
          digitalWrite(LED_PINO_QUENTE, HIGH);

          Serial.println("led amarelo");
        } else if (comando == "TEMPERATURA_FRIA") {
          digitalWrite(LED_PINO_FRIO, HIGH);
          digitalWrite(LED_PINO_QUENTE, LOW);
          digitalWrite(LED_PINO_ALERTA, LOW);
          Serial.println("led azul");
        }
      }
      cliente.stop();
    } else {
      Serial.println("falha ao conectar ao servidor");
    }
    delay(5000);  //5s

  }  //not nan

}  // loop