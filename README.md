# SolarMetrics - Módulo de Sensores IoT (ESP32 + MQTT + Node-RED)

Este módulo faz parte do ecossistema **SolarMetrics** e é responsável pela leitura e transmissão dos dados de corrente e tensão utilizando sensores acoplados ao **ESP32**, enviando-os via **MQTT** para o fluxo do **Node-RED**, que por sua vez redireciona os dados para APIs, dashboards ou sistemas de análise.

## Descrição Geral

Este repositório inclui:

- Código em **C++** para ESP32
- Comunicação MQTT com broker local ou remoto
- Fluxo Node-RED integrado
- Dashboard em Node-RED para visualização em tempo real

A leitura de corrente e tensão é feita por sensores conectados ao ESP32, que publica os dados em tópicos MQTT específicos. O Node-RED consome esses tópicos, processa os valores e envia para o backend ou exibe diretamente em dashboards.

---

## Arquitetura

```
[Sensores] -> [ESP32] -> [MQTT Broker] -> [Node-RED Flow] -> [Dashboard / API]
```

---

## Funcionalidades

- Leitura contínua de sensores analógicos
- Conexão Wi-Fi integrada via ESP32
- Publicação MQTT com intervalo configurável
- Fluxos automáticos do Node-RED para tratamento de dados
- Dashboard real-time

---

## Requisitos

### Hardware
- ESP32 (DevKit, WROOM ou similar)
- Sensor de corrente (ACS712, SCT-013, etc.)
- Sensor de tensão (ZMPT101B ou divisor resistivo)
- Cabos jumper e protoboard

### Software
- Arduino IDE ou PlatformIO
- Biblioteca PubSubClient
- Node-RED instalado
- Broker MQTT (Mosquitto recomendado)

---

## Código ESP32 (C++)

```cpp
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SEU_WIFI";
const char* password = "SENHA_WIFI";
const char* mqtt_server = "192.168.0.10"; // Endereço do broker

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      // conectado
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int sensorCorrente = analogRead(34);
  int sensorTensao = analogRead(35);

  String payload = String("{") +
                   "\"corrente\":" + sensorCorrente + "," +
                   "\"tensao\":" + sensorTensao + "}";

  client.publish("solarmetrics/sensores", payload.c_str());
  delay(2000);
}
```

---

## Fluxo Node-RED

O fluxo deve incluir:

- Nó de entrada MQTT (subscribe em `solarmetrics/sensores`)
- Nó function para converter dados brutos
- Nó de saída (API, dashboard ou banco de dados)

O fluxo em JSON será incluído no repositório.

---

## Dashboard

O dashboard inclui:

- Indicadores em tempo real (corrente, tensão)
- Gráficos históricos
- Status da conexão MQTT

Pode ser acessado via navegador após iniciar o Node-RED.

---

## Como rodar os serviços

1. Instale e configure o **Mosquitto MQTT Broker**
2. Suba o **Node-RED** via Docker ou localmente
3. Importe o fluxo incluído no repositório
4. Conecte o ESP32 à rede Wi-Fi
5. Visualize os dados no dashboard

---

## Estrutura do Repositório

```
/esp32
   |- codigo.cpp
/node-red
   |- fluxo.json
/dashboard
   |- layout.json
```

---

## Contato

Para suporte técnico ou melhorias, entre em contato com a equipe SolarMetrics.

