#ifdef __cplusplus
extern "C" {
#endif

#include "index.h"
#include "homebots.h"
#include "gpio.h"
#include "osapi.h"

static os_timer_t timer;

void togglePin(void *arg) {
  int state = GPIO_REG_READ(GPIO_OUT_ADDRESS) & BIT2;

  os_printf("-- GPIO2: %d \r\n", state);

  if (state > 0) {
      gpio_output_set(0, BIT2, BIT2, 0);
  } else {
      gpio_output_set(BIT2, 0, BIT2, 0);
  }
}

void loop() {}

void setup() {

  //Set GPIO2 to output mode
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

  //Set GPIO2 low
  gpio_output_set(0, BIT2, BIT2, 0);

  os_timer_setfn(&timer, (os_timer_func_t *)togglePin, NULL);
  os_timer_arm(&timer, 1000, 1);
}

#ifdef __cplusplus
}
#endif
