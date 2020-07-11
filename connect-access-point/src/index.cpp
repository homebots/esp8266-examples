#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG 1
#define WIFI_SSID       "esp8266_rocks"
#define WIFI_PASSWORD   "password"

#include "index.h"

const char HELLO[] = "HTTP 1/1 200 OK\n\n<h1>Hello!</h1>";

static os_timer_t wifiCheck;
LOCAL Wifi wifiConnection;

void setUserAndPassword(char* user, char* password) {
  wifiConnection.connectTo(user, password, true);
  system_restart();
}

void ICACHE_FLASH_ATTR checkStatus() {
  wifiConnection.printStatus();
  wifiConnection.printMacAddress();
  wifiConnection.printStationStatus();
}

void ICACHE_FLASH_ATTR onReceive(TcpServer* server, char* data, uint16_t length) {
  server->send((uint8_t*)HELLO);
}

void setup() {
  TcpServer server(80);

  os_timer_setfn(&wifiCheck, (os_timer_func_t*) &checkStatus, NULL);
  os_timer_arm(&wifiCheck, 5000, 1);

  // wifiConnection.useStatusLed(2);
  wifiConnection.disconnect();
  wifiConnection.startAccessPoint(WIFI_SSID, WIFI_PASSWORD);

  server.onReceive = (TcpReceiveCallback)onReceive;
  server.connect();
}

#ifdef __cplusplus
}
#endif
