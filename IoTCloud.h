#ifndef IOTCLOUD_H
#define IOTCLOUD_H

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "GlobalVariables.h"

void setupIoTCloud() {
  debugMessage("Initializing IoT Cloud...", INFO);

  // Initialize IoT Cloud connection
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Add IoT Properties
  ArduinoCloud.addProperty(pumpControl, READWRITE);
  ArduinoCloud.addProperty(notification, READ);
  ArduinoCloud.addProperty(pauseLoop, READWRITE);

  // Add schedule and runtime properties
  ArduinoCloud.addProperty(scheduleTimes, READWRITE); // Store schedule times as a comma-separated string
  ArduinoCloud.addProperty(scheduleCount, READWRITE); // Specify the number of active schedules
  ArduinoCloud.addProperty(runtimeDuration, READWRITE, "duration");

  debugMessage("IoT Cloud Initialized.", INFO);
}

#endif
