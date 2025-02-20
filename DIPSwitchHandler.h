#ifndef DIPSWITCHHANDLER_H
#define DIPSWITCHHANDLER_H

#include <Arduino.h>
#include "GlobalVariables.h"
#include "Debug.h"

void setupDIPSwitchHandler() {
  pinMode(SWITCH_PIN_PUMP, INPUT_PULLUP);
  pinMode(SWITCH_PIN_PROGRAMPAUSE, INPUT_PULLUP);
  debugMessage("DIP Switches Initialized.", INFO);
}

void handleSwitch() {
  static bool lastPumpState = HIGH, lastPauseState = HIGH;

  bool currentPumpState = digitalRead(SWITCH_PIN_PUMP);
  bool currentPauseState = digitalRead(SWITCH_PIN_PROGRAMPAUSE);

  if (currentPumpState != lastPumpState) {
    lastPumpState = currentPumpState;
    dipPumpControl = (currentPumpState == LOW);
    debugNotification(dipPumpControl ? "Pump Switch ON" : "Pump Switch OFF");
  }

  if (currentPauseState != lastPauseState) {
    lastPauseState = currentPauseState;
    dipPauseLoop = (currentPauseState == LOW);
    debugNotification(dipPauseLoop ? "Pause Switch ON" : "Pause Switch OFF");
  }
}

#endif
