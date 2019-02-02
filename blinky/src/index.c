#define UART_SPEED      115200

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

// extern "C" {
// #include "user_interface.h"
// }

void loop() {
  if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & BIT2) {
      //Set GPIO2 to LOW
      gpio_output_set(0, BIT2, BIT2, 0);
  } else {
      //Set GPIO2 to HIGH
      gpio_output_set(BIT2, 0, BIT2, 0);
  }

  os_delay_us(1000);
}

void setup() {
    gpio_init();

    //Set GPIO2 to output mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

    //Set GPIO2 low
    gpio_output_set(0, BIT2, BIT2, 0);
}