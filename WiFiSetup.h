#ifndef WIFISETUP_H
#define WIFISETUP_H

#include <WiFiS3.h>
#include "Debug.h"
#include "GlobalVariables.h"

void setupWiFi() {
  debugMessage("Connecting to Wi-Fi...", INFO);

  WiFi.begin(ssid, password);
  unsigned long startTime = millis();
  const unsigned long timeout = 30000;

  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startTime >= timeout) {
      debugNotification("Wi-Fi connection failed: Timeout.");
      return;
    }
    delay(1000);
  }

  debugNotification("Wi-Fi connected successfully.");
}

#endif
