#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>

const char* ssid = "***";
const char* password = "***";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void writeMessageOnWire(char* data) {
  Serial.println(data);

  Wire.beginTransmission(8);
  Wire.write(data);
  Wire.endTransmission();
}

void handleWebSocketMessage(void* arg, uint8_t* data, size_t len) {
  AwsFrameInfo* info = (AwsFrameInfo*) arg;

  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    writeMessageOnWire((char*) data);
  }
}

void websocketEventHandler(AsyncWebSocket* socket, AsyncWebSocketClient* client,
                           AwsEventType event_type, void* arg, uint8_t* data, size_t len) {
  switch (event_type) {
    case WS_EVT_CONNECT:
      Serial.println("[INFO] New client connected!");
      break;
    case WS_EVT_DISCONNECT:
      Serial.println("[INFO] Client disconnected!");
      writeMessageOnWire("stop");
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin(D1, D2);

  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  ws.onEvent(websocketEventHandler);

  server.addHandler(&ws);
  server.begin();
}

void loop() {
  ws.cleanupClients();
}
