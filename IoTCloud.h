#ifndef IOTCLOUD_H
#define IOTCLOUD_H

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "GlobalVariables.h" // Include global variables

void setupIoTCloud() {
  // Initialize IoT Cloud connection
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Add IoT Properties
  ArduinoCloud.addProperty(pumpControl, READWRITE);
  ArduinoCloud.addProperty(notification, READ); // Notification is read-only in IoT Cloud
  ArduinoCloud.addProperty(pauseLoop, READWRITE);
}

#endif
