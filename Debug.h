#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "GlobalVariables.h"

// Debug level constants
#define DEBUG 3
#define INFO 2
#define NOTIFY 1

// Set debug level here
#ifndef CURRENT_DEBUG_LEVEL
  #define CURRENT_DEBUG_LEVEL DEBUG
#endif

// Initialization function for Serial
void setupDebug() {
  Serial.begin(9600);
}

// General debug output function
void debugMessage(const String &message, int level) {
  if (level <= CURRENT_DEBUG_LEVEL) {
    if (level == DEBUG) Serial.println("[DEBUG] " + message);
    else if (level == INFO) Serial.println("[INFO] " + message);
    else if (level == NOTIFY) Serial.println("[NOTIFY] " + message);
  }
}

// Specialized function for notifications
inline void debugNotification(const String &message) {
  static String lastNotification;
  if (lastNotification != message) {
    lastNotification = message;
    notification = "[NOTIFY] " + message;
    debugMessage(message, NOTIFY);
  }
}

#endif
