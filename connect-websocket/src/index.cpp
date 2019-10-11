#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_SSID       "HomeBots"
#define WIFI_PASSWORD   "HomeBots"

#include "index.h"
#include "wifi.h"
#include "websocket.h"
#include "homebots.h"

static os_timer_t webSocketCheck;
static Wifi wifiConnection;
static ws_info webSocket;

void onReceive(struct ws_info *socket, int length, char *message, int opCode) {
  if (opCode == WS_OPCODE_TEXT) {
    os_printf("RECV %s\n", message);
  }
}

void ICACHE_FLASH_ATTR connectWebSocket() {
  if (!wifiConnection.isConnected()) {
    wifiConnection.printStatus();
    return;
  }

  if (webSocket.connectionState != CS_CONNECTED) {
    ws_connect(&webSocket, "ws://echo.websocket.org/");
    return;
  }

  os_printf("PING\n");
  ws_send(&webSocket, WS_OPCODE_TEXT, (char*)"PING", 5);
  os_timer_arm(&webSocketCheck, 5000, 1);
}

void ICACHE_FLASH_ATTR setup() {
  os_timer_setfn(&webSocketCheck, (os_timer_func_t *)connectWebSocket, NULL);
  os_timer_arm(&webSocketCheck, 1000, 1);

  wifiConnection.connectTo(WIFI_SSID, WIFI_PASSWORD);
  webSocket.onReceive = onReceive;
}

#ifdef __cplusplus
}
#endif
