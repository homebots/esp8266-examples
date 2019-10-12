#ifdef __cplusplus
extern "C" {
#endif

#include "index.h"
#include "homebots.h"
#include "ets_sys.h"
#include "gpio.h"
#include "osapi.h"

static os_timer_t loopTimer;
volatile uint8_t lastPin = -1;

LOCAL void pin0() {
  os_printf("pin 0\n");
}

LOCAL void pin2() {
  os_printf("pin 2\n");
}

void setup() {
  attachInterrupt(0, &pin0, Falling);
  attachInterrupt(2, &pin2, Rising);

  os_timer_setfn(&loopTimer, (os_timer_func_t *)onLoop, NULL);
  onLoop();
}

void onLoop() {
  armInterrupts();
  os_timer_disarm(&loopTimer);
  os_timer_arm(&loopTimer, 2000, 1);
}

#ifdef __cplusplus
}
#endif
