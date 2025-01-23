#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <Arduino.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

extern const char *ssid;
extern const char *password;
extern WiFiConnectionHandler ArduinoIoTPreferredConnection;

#define WATER_SENSOR_PIN 2
#define PUMP_PIN 5
#define SWITCH_PIN_PUMP 6
#define SWITCH_PIN_PROGRAMPAUSE 7

extern bool waterLow;
extern unsigned long pumpDuration;
extern unsigned long pumpStartTime;
extern bool pumpActive;
extern bool pauseLoop;
extern bool dipPauseLoop;
extern bool dipPumpControl;
extern bool rtcScheduledPumpActive; // Add this declaration

extern CloudSwitch pumpControl;
extern CloudString notification;

extern String scheduledTimes[4]; // Declare explicitly

#endif
