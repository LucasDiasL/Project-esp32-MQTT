#include <WiFi.h>          // Para conexões WiFi.
#include <ArduinoJson.h>   // Para manipulação de JSON.
#include <PubSubClient.h>  // Para MQTT

// Definições de credenciais WiFi e MQTT
const char* ssid = "Nome de sua rede wifi";
const char* password = "sua senha wifi!";

const char* mqtt_broker = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "umidade_temperatura";

// Definição do pino do sensor DHT11
#define DHT_PIN 33

WiFiClient espClient;      // Cliente WiFi
PubSubClient client(espClient);  // Cliente MQTT

// Função para conectar ao WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando ao WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Função de callback para o MQTT (não usada no seu código, mas necessária)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.print(topic);
  Serial.print(". Mensagem: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Função de reconexão MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao broker MQTT...");
    if (client.connect("esp32_temp")) {
      Serial.println("conectado");
      client.publish(mqtt_topic, "WIFI e Broker Conectados!");  // Removido .encode()
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  // Inicializa o monitor serial
  Serial.begin(115200);
  
  // Conecta ao WiFi
  setup_wifi();

  // Configura o MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  // Reconectar ao MQTT se necessário
  if (!client.connected()) {
    reconnect();
  }
  
  // Mantém a conexão MQTT ativa
  client.loop();

  // Leitura do sensor DHT11 (aqui, substituímos pela leitura de temperatura e umidade)
  float temperatura = random(20, 30); // Substitua com leitura real do DHT11
  float umidade = random(40, 60);    // Substitua com leitura real do DHT11

  // Criar o payload JSON
  StaticJsonDocument<200> payload_json;
  payload_json["temperatura"] = temperatura;
  payload_json["umidade"] = umidade;

  // Serializa o JSON para uma String
  String output;
  serializeJson(payload_json, output);

  // Publica o JSON no tópico MQTT
  client.publish(mqtt_topic, output.c_str());

  // Aguarda 5 segundos antes de enviar novamente
  delay(5000);
}
