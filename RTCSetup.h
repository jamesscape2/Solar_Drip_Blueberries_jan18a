#ifndef RTCSETUP_H
#define RTCSETUP_H

#include <NTPClient.h>
#include <WiFiUdp.h>
#include "GlobalVariables.h"
#include "Debug.h"

WiFiUDP ntpUDP;
const long utcOffsetSeconds = 8 * 3600;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetSeconds);

void setupRTC() {
  debugMessage("Initializing RTC...", INFO);
  timeClient.begin();

  if (!timeClient.update()) {
    debugMessage("RTC initialization failed: Unable to sync with NTP.", INFO);
    return;
  }

  debugMessage("RTC synchronized via NTP: " + timeClient.getFormattedTime(), INFO);
}

String getCurrentTime() {
  if (!timeClient.update()) debugMessage("RTC update failed.", DEBUG);
  return timeClient.getFormattedTime();
}

#endif
