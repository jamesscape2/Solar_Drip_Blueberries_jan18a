#ifndef WATERLEVELMONITOR_H
#define WATERLEVELMONITOR_H

#include "GlobalVariables.h"
#include "Debug.h"

void setupWaterLevelMonitor() {
  pinMode(WATER_SENSOR_PIN, INPUT_PULLUP);
  debugMessage("Water Level Monitor Initialized.", INFO);
}

void monitorWaterLevel() {
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 100;

  static bool lastWaterSensorState = HIGH;
  bool currentWaterSensorState = digitalRead(WATER_SENSOR_PIN);

  if (currentWaterSensorState != lastWaterSensorState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentWaterSensorState != waterLow) {
      waterLow = !currentWaterSensorState;

      if (!waterLow) {
        if (timeClient.update()) {
          debugNotification("Water level is good at " + timeClient.getFormattedTime());
        } else {
          debugNotification("Water level is good. Time unavailable.");
        }
        debugMessage("Water level is good.", INFO);
      } else {
        if (timeClient.update()) {
          debugNotification("Water level is low! Pump control disabled at " + timeClient.getFormattedTime());
        } else {
          debugNotification("Water level is low! Pump control disabled. Time unavailable.");
        }
        debugMessage("Water level is low!", INFO);
      }
    }
  }

  lastWaterSensorState = currentWaterSensorState;
}

#endif
