#include "GlobalVariables.h"

// Wi-Fi Credentials
const char *ssid = "WiFi-A2DF";
const char *password = "Basketball123!";
WiFiConnectionHandler ArduinoIoTPreferredConnection(ssid, password);

// Water Level Monitoring
bool waterLow = false;

// Pump Control
unsigned long pumpDuration = 15 * 60 * 1000; // Default runtime: 15 minutes
unsigned long pumpStartTime = 0;
bool pumpActive = false;

// Pause States
bool pauseLoop = false;
bool dipPauseLoop = false;
bool dipPumpControl = false;

// IoT Cloud Properties
CloudSwitch pumpControl;
CloudString notification;
CloudString scheduleTimes = "07:00,10:00,14:00,17:00"; // Default schedule times
CloudInt scheduleCount = 4;                           // Default number of schedules
CloudTime runtimeDuration = 15 * 60 * 1000;           // Default runtime duration (15 minutes)

// RTC-Based Scheduled Control
bool rtcScheduledPumpActive = false;
