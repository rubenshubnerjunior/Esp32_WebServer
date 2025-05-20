

/*
 * Este codigo eh um exemplo de um servidor de pagina web que está na memoria nao volatil SPIFFS
 * Quando a pagina eh transferida para o navegador o script  "logica.js" do navegador 
 * usa o webSocket para trocar mensagens com o Esp32 de maneira assincrona.
 * 
 * O display I2C usa os pinos:
 * SDA--> GPIO 21
 * SCL--> GPIO 22
 * 
 * Led 1 GPIO 19 com 180 ohms em serie katodo no GND
 * Led 2 GPIO 18 com 180 ohms em serie katodo no GND
 * 
 * Pino do ADC 1 --> GPIO 36 maxima tensao entrada 3.3 V
 * Pino do ADC 2 --> GPIO 39 maxima tensao entrada 3.3 V
 * 
 * Arduino IDE 1.8.19
 * Core Esp32-> 3.2.0
 * 
 */



#include "SPIFFS.h"
#include <ArduinoJson.h>
#include <AsyncTCP.h> // Pagina web de configuracao local
#include "ESPAsyncWebServer.h" // websocket com pagina web local de configuracao
#include <LiquidCrystal_I2C.h> // Pasta inserida em: C:\Program Files (x86)\Arduino\libraries

//===================Variaveis Globais===============================
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

const char* ssid = "hubner"; // Troque pelo seu SSID
const char* password =  "@txtv3457"; // Insira a sua Senha

AsyncWebServer server(80); // Transfere arquivos de Front End para o navegador
AsyncWebSocket ws("/ws"); // Envia e recebe mensagens da logica no navegador com a logica no Esp32

String led1 = "off";
String led2 = "off";
String adc1 = "0.0"; 
String adc2 = "0.0";

long tempoSendMsg = 0; // Tempo de envio de mensagens para o navegador


const int pinADC1 = 36; // GPIO 36 (Analog ADC1_CH0)
const int pinADC2 = 39; // GPIO 39 (Analog ADC1_CH3)

const int swLed1 = 19; // pino ligar/desligar led 1
const int swLed2 = 18; // pino ligar/desligar led 2

//=================Leituras dos ADCs================================
void getAds()
{

  int auxADC1 = analogRead(pinADC1); // Numero inteiro até 4095
  int auxADC2 = analogRead(pinADC2);

  float fADC1 = (3.3/4095)*auxADC1; // Calcula o range
  float fADC2 = (100.0/4095)*auxADC2;

  String stADC1 = String(fADC1); //Converte float para String
  String stADC2 = String(fADC2); //Converte float para String

  adc1 = stADC1; // Atualiza os valor do ADC1
  adc2 = stADC2; // Atualiza os valor do ADC1
}

//================Envio de status via websocket para o navegador========================
void enviaStatusNavegador()
{

  DynamicJsonDocument doc(2048); // Documento JSON

  doc["adc1"] = adc1;
  doc["adc2"] = adc2; // Insere valores nas chaves do objeto Json
  doc["led1"] = led1;
  doc["led2"] = led2;
  String result = "";
  serializeJson(doc,result); // Converte JSON para String para ser enviado por webSocket
  Serial.println("Json para enviar-->" + result);
  ws.textAll(result); // Envia para todos os clientes "Navegadores"
}

//===============Trata a string recebida do Esp32 e atualiza status dos Leds===========================
void trataString(String msgRecebida)
{
   DynamicJsonDocument doc(2048);
   deserializeJson(doc, msgRecebida); // Converte String para objeto JSON
   JsonObject obj = doc.as<JsonObject>();

  String jsonLed1 = obj[String("led1")]; // leitura do valor da chave "led1" do objeto Json
  String jsonLed2 = obj[String("led2")]; // leitura do valor da chave "led2" do objeto Json

  led1 = jsonLed1; // Status do Led 1 // atualiza a vaviavel global led1
  led2 = jsonLed2; // Status do Led 2 // atualiza a vaviavel global led2

  
  Serial.println("led 1-->" + led1);
  Serial.println("led 2-->" + led2);


  if(led1=="on") digitalWrite(swLed1, HIGH);
  if(led2=="on") digitalWrite(swLed2, HIGH);

  if(led1=="off") digitalWrite(swLed1, LOW);
  if(led2=="off") digitalWrite(swLed2, LOW);

  
}
//=======Mensagens recebidas do  navegador via  Websocket===================

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;

    String msgRecebida = (char*)data; // Mensagem recebida do navegador (botoes on/off dos leds)
    Serial.println("String Json do Navegador:");
    Serial.println(msgRecebida); // String com formato para converter em objeto JSON
    trataString(msgRecebida);
  
  }
}

//==============Eventos do Websocket funciona de modo assincrono=======================================
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      enviaStatusNavegador(); // Na conexao envia a String Json para informar os status atual do Esp32
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

//=========Inicia o webSocket para mensagens de configuracao do ESP32=======
void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}
//=============Inicia Servidores e atende requests do navegador ( Arquivos Front End )================
void startServidores()
{
  Serial.println("Iniciando Servidor de Configuracao do Esp32.....");

  initWebSocket(); // Mensagens da web page com o ESP32
  server.begin(); //Inicia o Servidor web para config. local

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) { //Envia html para o navegador
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/src/bootstrap.bundle.min.js", HTTP_GET, [](AsyncWebServerRequest * request) { //Envia .js do bootstrap para o navegador
    request->send(SPIFFS, "/src/bootstrap.bundle.min.js", "text/javascript");
  });

  server.on("/src/jquery-3.3.1.js", HTTP_GET, [](AsyncWebServerRequest * request) { //Envia jquery para o navegador
    request->send(SPIFFS, "/src/jquery-3.3.1.js", "text/javascript");
  });

  server.on("/src/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest * request) { //Envia css do bootstrap para o navegador
    request->send(SPIFFS, "/src/bootstrap.min.css", "text/css");
  });

  server.on("/logica.js", HTTP_GET, [](AsyncWebServerRequest * request) { //Envia logica.js para o navegador
    request->send(SPIFFS, "/logica.js", "text/css");
  });

  server.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest * request) { //Envia logo.png para o navegador
    request->send(SPIFFS, "/logo.png", "image/png");
  });
}
//======================Conecta com o WIFI=====================================

void conectaWIFI()
{

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.println("Conectando com o  WiFi.."); 
  delay(1000);
 }
 Serial.println("Conectado com o WIFI");
 showDisplay("WIFI conectado", WiFi.localIP().toString());
  
}
//==================Funcao para exibir o display lcd============================
void showDisplay(String linha1, String linha2)
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha1);

  lcd.setCursor(0, 1);
  lcd.print(linha2);
}

//======================================setup()=============================
void setup()
{
  Serial.begin(115200);   // Iniciamos a serial com velocidade de 115200

  lcd.init();
  lcd.backlight();

  showDisplay("Display", "Iniciado"); // Mostra mensagens na linha 1 e linha 2 do display
  delay(1000);

  if (!SPIFFS.begin())// Habilita o uso da memoria SPIFFS
  { 
    Serial.println("Ocorreu erro ao montar a SPIFFS");
    return;
  }


  pinMode(swLed1, OUTPUT); // pino do Led1 como output
  pinMode(swLed2, OUTPUT); // pino do Led2 como output
  digitalWrite(swLed1, LOW); // Inicia os Leds apagados
  digitalWrite(swLed2, LOW);
  

  conectaWIFI();
  startServidores();
  
  
}

//=======================================loop()
void loop()
{
  long now = millis(); // Tempo decorrido do programa iniciado 
   ws.cleanupClients(); // Remove clientes inativos

  if (now - tempoSendMsg  > 1000)
  {
     getAds();
     enviaStatusNavegador();
     tempoSendMsg = now;
  }

  
}
