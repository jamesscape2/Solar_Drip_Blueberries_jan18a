#ifndef PUMPCONTROL_H
#define PUMPCONTROL_H

#include <Arduino.h>
#include "GlobalVariables.h"
#include "RTCSetup.h"
#include "Debug.h"
//#include "LEDControl.h"

void setupPumpControl() {
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  debugMessage("Pump Control Initialized.", INFO);
}

void activatePump() {
  debugMessage("Pump activated.", INFO);
  digitalWrite(PUMP_PIN, HIGH);
  //displayPumpOnSymbol();
  pumpStartTime = millis();
  pumpActive = true;
}

void stopPump() {
  debugMessage("Pump deactivated.", INFO);
  digitalWrite(PUMP_PIN, LOW);
  //displayPumpOffSymbol();
  pumpActive = false;
}

void controlPump() {
  if (pumpActive && (millis() - pumpStartTime >= pumpDuration)) {
    stopPump();
  }
}

void checkAndRunScheduledPump() {
  String currentTime = getCurrentTime();
  String currentHourMinute = currentTime.substring(0, 5);

  for (String scheduledTime : scheduledTimes) {
    if (currentHourMinute == scheduledTime) {
      if (!rtcScheduledPumpActive && !pumpActive) {
        debugMessage("Starting pump for scheduled cycle.", INFO);
        monitorWaterLevel();
        if (waterLow) {
          stopPump();
          debugNotification("Water Low, Cycle Stopped");
          debugMessage("Water Low, Cycle Stopped", INFO);
        } else {
          activatePump();
        }
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
