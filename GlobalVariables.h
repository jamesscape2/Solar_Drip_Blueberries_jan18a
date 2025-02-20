#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <Arduino.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "Config.h"

// Wi-Fi credentials
extern const char *ssid;
extern const char *password;

// IoT Cloud connection
extern WiFiConnectionHandler ArduinoIoTPreferredConnection;

// Pump and water level states
extern bool waterLow;
extern unsigned long pumpDuration;
extern unsigned long pumpStartTime;
extern bool pumpActive;

// Pause states
extern bool pauseLoop;
extern bool dipPauseLoop;
extern bool dipPumpControl;

// IoT Cloud properties
extern CloudSwitch pumpControl;
extern CloudString notification;
extern CloudString scheduleTimes; // Comma-separated schedule times
extern CloudInt scheduleCount;    // Number of active schedule times
extern CloudTime runtimeDuration; // Editable runtime duration in milliseconds

// Runtime control
extern bool rtcScheduledPumpActive;

#endif
