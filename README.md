![Logo](banner.jpg)
# SolarMetrics - Módulo de Sensores IoT (ESP32 + MQTT + Node-RED)

Este módulo faz parte do ecossistema **SolarMetrics** e é responsável pela leitura e transmissão dos dados de corrente e tensão utilizando sensores acoplados ao **ESP32**, enviando-os via **MQTT** para o fluxo do **Node-RED**, que por sua vez redireciona os dados para APIs, dashboards ou sistemas de análise.

## Descrição Geral

Este repositório inclui:

- Código em **C++** para ESP32
- Comunicação MQTT com broker local ou remoto
- Fluxo Node-RED integrado
- Dashboard para visualização em tempo real

A leitura de corrente e tensão é feita por sensores conectados ao ESP32, que publica os dados em tópicos MQTT específicos. O Node-RED consome esses tópicos, processa os valores e envia para o backend ou exibe diretamente em dashboards.

---

## Arquitetura

```
[Sensores] -> [ESP32] -> [MQTT Broker] -> [Node-RED] -> [Dashboard / API]
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
- Broker MQTT

---

## Código ESP32 (C++)

O funcionamento do sistema ocorre da seguinte forma: o ESP32 conecta à rede Wi-Fi e, em seguida, se conecta ao broker MQTT. Após isso, ele simula dados de sensores, calcula a potência, constrói um JSON com as informações e publica os dados no tópico MQTT configurado. Esse processo é repetido continuamente.
---

## Fluxo Node-RED

O fluxo deve incluir:

- Nó de entrada MQTT (subscribe em `sensor/control`)
- Nó function para converter dados brutos
- Nó de saída (API, dashboard ou banco de dados)

O fluxo em JSON será incluído no repositório.

---

## Dashboard

O dashboard inclui:

- Indicadores em tempo real (corrente, tensão)
- Gráficos históricos
- Status do sistema

Pode ser acessado via navegador após iniciar o live server do dashboard.

---

## Como rodar os serviços

1. Inicie o **Node-RED** localmente em sua máquina (`node-red` no terminal) e importe o fluxo disponível no repositório.
2. Configure o broker MQTT conforme indicado no fluxo.
3. Conecte o **ESP32** à rede Wi-Fi para iniciar o envio dos dados.
4. Abra o **VS Code** e acesse a pasta do repositório.
5. Abra o arquivo `index.html` e inicie o **Live Server** para visualizar os dados em tempo real.

---

## Estrutura do Repositório

```
/
   |- fluxo-node.json
   |- codigo-fonte.ino
   |- index.html
```

---

**SolarMetrics** — Sua energia. Seu controle  ☀️

