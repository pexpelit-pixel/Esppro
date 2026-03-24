#include <WiFi.h>
#include "esp_wifi.h"
#include "lwip/lwip_napt.h"

#define MAX_CLIENTS 1

// WIFI SUMBER
const char* sta_ssid = "PRASATI";
const char* sta_pass = "leoputta";

// HOTSPOT ESP
const char* ap_ssid = "GAME_ONLY";
const char* ap_pass = "12345678";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);

  WiFi.begin(sta_ssid, sta_pass);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP STA: ");
  Serial.println(WiFi.localIP());

  IPAddress apIP(192, 168, 4, 1);
  IPAddress netMsk(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, netMsk);

  WiFi.softAP(ap_ssid, ap_pass, 1, 0, MAX_CLIENTS);

  Serial.println("Hotspot aktif!");
  Serial.print("IP AP: ");
  Serial.println(WiFi.softAPIP());

  ip_napt_init(1000, 10);
  ip_napt_enable(WiFi.softAPIP(), 1);

  Serial.println("NAT aktif");
  esp_wifi_set_ps(WIFI_PS_NONE);
}

void loop() {
  wifi_sta_list_t stationList;
  esp_wifi_ap_get_sta_list(&stationList);

  Serial.print("Connected device: ");
  Serial.println(stationList.num);

  delay(5000);
}
