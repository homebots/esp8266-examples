#ifdef __cplusplus
extern "C" {
#endif

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

void loop() {
  togglePin(wifiConnection.isConnected());
}

void ICACHE_FLASH_ATTR
printStatus(void) {
  wifiConnection.printStatus();

  if (!wifiConnection.isConnected()) {
    os_timer_disarm(&timer);
    os_timer_arm(&timer, 1000, 1);
  }
}

void setup() {
  gpio_init();
  gpio_output_set(0, BIT2, BIT2, 0);

  os_timer_setfn(&timer, (os_timer_func_t *)printStatus, NULL);
  os_timer_arm(&timer, 1000, 1);

  wifiConnection.connectTo("HomeBots", "HomeBots");
}

#ifdef __cplusplus
}
#endif
