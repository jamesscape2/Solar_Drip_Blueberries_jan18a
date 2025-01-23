#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "GlobalVariables.h"

// Enable or disable debug notifications (set to 1 to enable, 0 to disable)
#define DEBUG_NOTIFICATIONS 1

// Debug level constants
#define NO_OUTPUT 0
#define INFO 1
#define DEBUG 2

// Set the desired debug level by changing this value
#ifndef CURRENT_DEBUG_LEVEL
  #define CURRENT_DEBUG_LEVEL 1 // Default level
#endif

// Initialization function for Serial
void setupDebug() {
  Serial.begin(9600);
}

// Core debug output function
void debugMessage(const String &message, int level) {
  if (level <= CURRENT_DEBUG_LEVEL) { // Check if the message should be displayed
    if (level == DEBUG) Serial.println("[DEBUG] " + message);
    else if (level == INFO) Serial.println("[INFO] " + message);
  }
}

// Notification function with preprocessor control
#if DEBUG_NOTIFICATIONS
  inline void debugNotification(const String &message) {
    static String lastNotification; // Tracks the last notification to avoid repeats
    if (lastNotification != message) {
      lastNotification = message;
      notification = ("[NOTIFY] " + message);
    }
  }
#else
  inline void debugNotification(const String &message) {
    // Empty implementation if notifications are disabled
  }
#endif

#endif // DEBUG_H
