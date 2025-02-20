#ifndef WATERLEVELMONITOR_H
#define WATERLEVELMONITOR_H

#include "GlobalVariables.h"
#include "Debug.h"

void setupWaterLevelMonitor() {
  pinMode(WATER_SENSOR_PIN, INPUT_PULLUP);
  debugMessage("Water Level Monitor Initialized.", INFO);
}

void monitorWaterLevel() {
  static bool lastState = HIGH;
  bool currentState = digitalRead(WATER_SENSOR_PIN);

  if (currentState != lastState) {
    delay(50); // Debounce
    if (currentState == digitalRead(WATER_SENSOR_PIN)) {
      lastState = currentState;
      waterLow = (currentState == LOW);

      String time = getCurrentTime();
      debugNotification(waterLow ? "Water level is low! " + time : "Water level is good! " + time);
    }
  }
}

#endif
