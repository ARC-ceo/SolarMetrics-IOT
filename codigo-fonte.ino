#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Definições de pinos
#define LED_BUILTIN 2   // LED onboard

// Configurações Wi-Fi
const char* ssid = "Carlos HC";
const char* password = "969141242";

// Configurações MQTT
const char* mqtt_server = "192.168.15.93";
const int mqtt_port = 1883;
const char* mqtt_user = "solarmetrics";
const char* mqtt_password = "solarmetricswinchallenge";
const char* mqtt_topic = "sensor/control";

// Identificadores
const char* ID = "561187";
const char* moduleID = "SM_ESP32";

// Objetos
WiFiClient espClient;
PubSubClient client(espClient);
JsonDocument doc;
char buffer[256];

// Variáveis
float tensaoGeracao;
float correnteGeracao;
float tensaoConsumo;
float correnteConsumo;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(moduleID, mqtt_user, mqtt_password)) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

float simularTensao(float tensaoMin, float tensaoMax) {
  return random(tensaoMin * 100, tensaoMax * 100) / 100.0;
}

float simularCorrente(float correnteMin, float correnteMax) {
  return random(correnteMin * 100, correnteMax * 100) / 100.0;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
  Serial.begin(115200);
  
  setup_wifi();
  
  client.setServer(mqtt_server, mqtt_port);
  }

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura dos sensores
  tensaoGeracao = simularTensao(110.0, 130.0);
  correnteGeracao = simularCorrente(10.5, 20.0);

  tensaoConsumo = simularTensao(110.0, 130.0);
  correnteConsumo = simularCorrente(0.5, 10.0);

  // Limpa o documento JSON
  doc.clear();

  // Monta o JSON
  doc["ID"] = ID;
  doc["Sensor"] = moduleID;
  doc["IP"] = WiFi.localIP().toString();
  doc["MAC"] = WiFi.macAddress();

  if (!isnan(tensaoGeracao) && !isnan(correnteGeracao) && !isnan(tensaoConsumo) && !isnan(correnteConsumo)) {
    doc["GeracaoWatt"] = round(tensaoGeracao * correnteGeracao);
    doc["ConsumoWatt"] = round(tensaoConsumo * correnteConsumo);
  } else {
    doc["GeracaoWatt"] = "Erro na leitura";
    doc["ConsumoWatt"] = "Erro na leitura";
  }

  // Serializa o JSON
  serializeJson(doc, buffer);
  
  // Publica no MQTT
  client.publish(mqtt_topic, buffer);
  
  // Feedback visual
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println(buffer);
  delay(3000);
} 