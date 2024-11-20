# Projeto ESP32 - Leitura de Temperatura e Umidade via MQTT

Este projeto utiliza o **ESP32** para conectar-se a uma rede **Wi-Fi**, ler dados de um **sensor DHT11** (ou valores simulados) e enviar os dados para um **broker MQTT**. O projeto também utiliza a biblioteca **ArduinoJson** para gerar os dados no formato JSON e a **PubSubClient** para gerenciar a comunicação MQTT.

## Funcionalidade

- Conexão com a rede **Wi-Fi** utilizando credenciais definidas no código.
- Leitura de **temperatura** e **umidade** (simulada no código) usando o sensor DHT11.
- Publicação dos dados de temperatura e umidade em um **broker MQTT** usando o protocolo MQTT.
- O JSON gerado contém os dados de temperatura e umidade e é enviado para o tópico `umidade_temperatura` no broker MQTT.

## Requisitos

### Hardware
- **Placa ESP32** (exemplo: ESP32 Dev Module).
- **Sensor DHT11** (opcional, pois os valores de temperatura e umidade são gerados aleatoriamente no código para testes).
- Fios para conectar o DHT11 (se estiver usando o sensor físico).

### Software
- **Arduino IDE** configurado para programar o **ESP32**.
- Bibliotecas:
  - `WiFi.h` (incluída no pacote ESP32).
  - `ArduinoJson` (para manipulação de JSON).
  - `PubSubClient` (para comunicação MQTT).

## Como Configurar

### 1. Instalar o ESP32 no Arduino IDE
Se você ainda não tem o ESP32 instalado no seu Arduino IDE, siga os passos abaixo:
1. Abra o Arduino IDE.
2. Vá em **Arquivo** > **Preferências** e no campo "URLs Adicionais de Gerenciadores de Placas", adicione:
