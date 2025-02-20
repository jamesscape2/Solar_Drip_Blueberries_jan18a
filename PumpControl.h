#ifndef PUMPCONTROL_H
#define PUMPCONTROL_H

#include <Arduino.h>
#include "GlobalVariables.h"
#include "RTCSetup.h"
#include "Debug.h"

// Helper function to parse schedule times from the comma-separated string
void parseScheduleTimes(String times[], int &count) {
  int currentIndex = 0;
  int commaIndex;

  while ((commaIndex = scheduleTimes.indexOf(',', currentIndex)) != -1 && count < scheduleCount) {
    times[count++] = scheduleTimes.substring(currentIndex, commaIndex);
    currentIndex = commaIndex + 1;
  }

  if (count < scheduleCount && currentIndex < scheduleTimes.length()) {
    times[count++] = scheduleTimes.substring(currentIndex);
  }
}

void setupPumpControl() {
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  debugMessage("Pump Control Initialized.", INFO);
}

void activatePump() {
  debugMessage("Pump activated.", INFO);
  digitalWrite(PUMP_PIN, HIGH);
  pumpStartTime = millis();
  pumpActive = true;
}

void stopPump() {
  debugMessage("Pump deactivated.", INFO);
  digitalWrite(PUMP_PIN, LOW);
  pumpActive = false;
}

void checkAndRunScheduledPump() {
  String currentTime = getCurrentTime().substring(0, 5);
  String parsedTimes[10]; // Temporary array to store parsed times
  int count = 0;

  // Parse the schedule times from the CloudString
  parseScheduleTimes(parsedTimes, count);

  for (int i = 0; i < count; i++) {
    if (currentTime == parsedTimes[i] && !rtcScheduledPumpActive && !pumpActive) {
      debugMessage("Starting scheduled pump cycle.", INFO);

      if (waterLow) {
        stopPump();
        debugNotification("Water Low, Cycle Stopped.");
      } else {
        pumpDuration = runtimeDuration; // Use IoT Cloud-configured runtime
        activatePump();
        rtcScheduledPumpActive = true;
      }
    }
  }

  if (rtcScheduledPumpActive && (millis() - pumpStartTime >= pumpDuration)) {
    stopPump();
    rtcScheduledPumpActive = false;
    debugMessage("Scheduled pump cycle complete.", INFO);
  }
}

#endif
