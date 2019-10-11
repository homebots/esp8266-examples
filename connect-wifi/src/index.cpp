#ifdef __cplusplus
extern "C" {
#endif

#define WIFI_SSID       "HomeBots"
#define WIFI_PASSWORD   "HomeBots"

#include "index.h"
#include "c_types.h"
#include "gpio.h"
#include "osapi.h"
#include "homebots.h"
#include "wifi.h"

static os_timer_t timer;
Wifi wifiConnection;

void togglePin(bool on) {
  if (on) {
    gpio_output_set(BIT2, 0, BIT2, 0);
  } else {
    gpio_output_set(0, BIT2, BIT2, 0);
  }
}

void ICACHE_FLASH_ATTR
printStatus(void) {
  togglePin(wifiConnection.isConnected());

  wifiConnection.printStatus();

  os_timer_disarm(&timer);
  os_timer_arm(&timer, 1000, 1);
}

void setup() {
  gpio_output_set(0, BIT2, BIT2, 0);

  os_timer_setfn(&timer, (os_timer_func_t *)printStatus, NULL);
  os_timer_arm(&timer, 1000, 1);

  wifiConnection.connectTo(WIFI_SSID, WIFI_PASSWORD);
}

#ifdef __cplusplus
}
#endif
