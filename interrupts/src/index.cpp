#ifdef __cplusplus
extern "C" {
#endif

#include "index.h"
#include "homebots.h"
#include "ets_sys.h"
#include "gpio.h"
#include "osapi.h"

static os_timer_t interruptCallback;
static uint32_t interrupt_reg = 0;
static uint16_t gpioStatus = -1;

void loop() {}

void onButtonPress() {
  if (gpioStatus & BIT2) {
    os_printf("Press IO 2 %d", isHigh(2));
  }

  if (gpioStatus == 0) {
    os_printf("Press IO 0 %d", isHigh(0));
  }

  os_printf("INTR %.8x", gpioStatus);
}

void onInterrupt(void*) {
  ETS_GPIO_INTR_DISABLE();

  uint16_t gpioStatus = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
  GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpioStatus);

  os_timer_arm(&interruptCallback, 1, 0);

  ETS_GPIO_INTR_ATTACH(onInterrupt, NULL);
  ETS_GPIO_INTR_ENABLE();
}

void setup() {
  PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO2_U);
  PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO0_U);
  GPIO_DIS_OUTPUT(GPIO_ID_PIN(2));

  os_timer_setfn(&interruptCallback, (os_timer_func_t *)onButtonPress, NULL);
  gpio_pin_intr_state_set(GPIO_ID_PIN(2), GPIO_PIN_INTR_POSEDGE);

  ETS_GPIO_INTR_DISABLE();
  ETS_GPIO_INTR_ATTACH(onInterrupt, NULL);
  ETS_GPIO_INTR_ENABLE();
}

#ifdef __cplusplus
}
#endif
