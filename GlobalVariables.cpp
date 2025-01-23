#include "GlobalVariables.h"
#include <ArduinoIoTCloud.h>

const char *ssid = "WiFi-A2DF";
const char *password = "Basketball123!";
WiFiConnectionHandler ArduinoIoTPreferredConnection(ssid, password);

bool waterLow = false;
unsigned long pumpDuration = 15 * 60 * 1000; // 15 minutes in milliseconds
unsigned long pumpStartTime = 0;
bool pumpActive = false;
bool pauseLoop = false;
bool dipPauseLoop = false;
bool dipPumpControl = false;
bool rtcScheduledPumpActive = false; // Define the variable

CloudSwitch pumpControl;
CloudString notification;

String scheduledTimes[4] = {"07:00", "10:00", "14:00", "17:00"};
