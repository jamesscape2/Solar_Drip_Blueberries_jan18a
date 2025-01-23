#ifndef DIPSWITCHHANDLER_H
#define DIPSWITCHHANDLER_H

#include <Arduino.h>
#include "GlobalVariables.h"
#include "PumpControl.h"
#include "Debug.h"

void onSwitchPump();
void onSwitchPause();

volatile bool dipPumpStateChanged = false;
volatile bool dipPauseStateChanged = false;

void setupDIPSwitchHandler() {
  pinMode(SWITCH_PIN_PUMP, INPUT_PULLUP);
  pinMode(SWITCH_PIN_PROGRAMPAUSE, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN_PUMP), onSwitchPump, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN_PROGRAMPAUSE), onSwitchPause, CHANGE);
}

void onSwitchPump() {
  dipPumpStateChanged = true;
}

void onSwitchPause() {
  dipPauseStateChanged = true;
}

void handleSwitch() {
  if (dipPumpStateChanged) {
    dipPumpControl = !digitalRead(SWITCH_PIN_PUMP);
    debugNotification(dipPumpControl ? "DIP Switch Pump Activated" : "DIP Switch Pump Deactivated");
    dipPumpStateChanged = false;
  }

  if (dipPauseStateChanged) {
    dipPauseLoop = !digitalRead(SWITCH_PIN_PROGRAMPAUSE);
    debugNotification(dipPauseLoop ? "DIP Switch Pause Activated" : "DIP Switch Pause Deactivated");
    dipPauseStateChanged = false;
  }
}

#endif
