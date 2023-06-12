
// Librarys to include
#include <Arduino.h>
#include <ArduinoOTA.h>
// Dependencies
#include "ArduinoJson.h"

// Network libraries
#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"

#include "const.h"

#ifndef CLIENT_SSID
#define CLIENT_SSID DEFAULT_CLIENT_SSID
#endif

#ifndef CLIENT_PASS
#define CLIENT_PASS ""
#endif

// Define Globals
#define MIR_GLOBAL
#define _INIT(x) = x
#define _INIT_N(x)
#define MIR_AP_PASS DEFAULT_AP_PASS

// Globals
MIR_GLOBAL char apSSID[33] _INIT(DEFAULT_AP_SSID);
MIR_GLOBAL byte apChannel _INIT(1); // 2.4GHz WiFi AP channel (1-13)
MIR_GLOBAL byte apHide _INIT(0);
MIR_GLOBAL char clientSSID[33] _INIT(CLIENT_SSID);
MIR_GLOBAL char clientPass[65] _INIT(CLIENT_PASS);
MIR_GLOBAL char apPass[65] _INIT(MIR_AP_PASS);
MIR_GLOBAL char otaPass[33] _INIT(DEFAULT_OTA_PASS);
