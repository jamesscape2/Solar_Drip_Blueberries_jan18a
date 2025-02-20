
#include "WiFiSetup.h"
#include "RTCSetup.h"
#include "WaterLevelMonitor.h"
#include "PumpControl.h"
#include "IoTCloud.h"
#include "Debug.h"
//#include "LEDControl.h"
#include "DIPSwitchHandler.h"

void setup() {
  setupDebug();
  debugMessage("Starting Setup...", INFO);

  setupPumpControl();
  setupWiFi();
  setupIoTCloud();
  setupRTC();
  setupWaterLevelMonitor();
  setupDIPSwitchHandler();
  //initLEDMatrix();

  debugMessage("Setup Complete", INFO);
}

void loop() {
  ArduinoCloud.update();
  handleSwitch();

  if (pauseLoop || dipPauseLoop) {
    stopPump();
    debugNotification("Program Paused");
    while (pauseLoop || dipPauseLoop) {
      ArduinoCloud.update();
      handleSwitch();
    }
    debugNotification("Program Restarted");
  }

  monitorWaterLevel();
  if (!waterLow && (pumpControl || dipPumpControl)) {
    activatePump();
  } else if (waterLow || (!pumpControl && !dipPumpControl)) {
    stopPump();
  }

  checkAndRunScheduledPump();
}
