#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_SSID       "esp8266_rocks"
#define WIFI_PASSWORD   "password"

#include "index.h"
#include "homebots.h"
#include "wifi.h"

void setup() {
  Wifi wifiConnection;
  wifiConnection.useStatusLed(2);
  wifiConnection.startAccessPoint(WIFI_SSID, WIFI_PASSWORD);
}

#ifdef __cplusplus
}
#endif
