#ifdef __cplusplus
extern "C" {
#endif

#include "index.h"
#include "wifi.h"
#include "ntp.h"
#include "websocket.h"
#include "homebots.h"

static os_timer_t webSocketCheck;
static Wifi wifiConnection;
static ws_info webSocket;
// static NTP ntp;

#define CS_CONNECTED 3
#define WS_OPCODE_TEXT 0x1
#define WS_OPCODE_BINARY 0x2

void ICACHE_FLASH_ATTR onReceive(struct ws_info *wsInfo, int length, char *message, int opCode) {
  switch (opCode) {
    case WS_OPCODE_BINARY:
      break;

    case WS_OPCODE_TEXT:
      os_printf("%d %s\n", length, message);
      ws_send(wsInfo, WS_OPCODE_TEXT, message, length);
      break;
  }
}

void ICACHE_FLASH_ATTR loop() {
  // ntp.sync();
}

void ICACHE_FLASH_ATTR connectWebSocket() {
  if (!wifiConnection.isConnected()) {
    wifiConnection.printStatus();
    return;
  }

  // if (!ntp.isReady()) {
  //   os_printf("Waiting for NTP: %lu", ntp.interval);
  //   return;
  // }

  if (webSocket.connectionState != CS_CONNECTED) {
    ws_connect(&webSocket, "ws://hub.homebots.io/hub");
    return;
  }

  os_timer_arm(&webSocketCheck, 5000, 1);
}

void ICACHE_FLASH_ATTR setup() {
  os_timer_setfn(&webSocketCheck, (os_timer_func_t *)connectWebSocket, NULL);
  os_timer_arm(&webSocketCheck, 1000, 1);

  wifiConnection.connectTo("HomeBots", "HomeBots");
  // ntp.start();
  webSocket.onReceive = onReceive;
}

#ifdef __cplusplus
}
#endif
