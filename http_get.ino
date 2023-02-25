#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>

const int led = 2;
const int button = 3;
const char* ssid = "*****";
const char* pass = "*****";

Adafruit_NeoPixel pixels(1, led, NEO_GRB + NEO_KHZ800);
WiFiClientSecure secureClient;
HTTPClient http;

void setup() {
  secureClient.setInsecure();
  Serial.begin(115200);
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(50, 50, 50));
  pixels.show();
  pinMode(button, INPUT_PULLUP);
  while (!Serial);

  // connection wifi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("wifi connected");
  Serial.println(WiFi.localIP());
}

void loop() {
  int temp = 18;
  int humi = 70;
  char url[256];
  // webApps url ↓
  sprintf(url, "********?temp=%d&humi=%d", temp, humi);

  if (!http.begin(secureClient, url)) {
    Serial.println("faild httpclient begin");
    for (int i = 0; i < 6; i++) {
      if (i % 2 == 0) pixels.setPixelColor(0, pixels.Color(50, 0, 0));
      else pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
      delay(100);
    }
    return;
  }

  http.addHeader("Content-Type", "application/json");
  int res = http.GET();
  String body = http.getString();
  Serial.println(res);
  Serial.println(body);
  http.end();

  delay(10000);
}
