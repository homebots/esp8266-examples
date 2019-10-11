#ifdef __cplusplus
extern "C"
{
#endif

#include "index.h"
#include "wifi.h"
#include "websocket.h"
#include "homebots.h"
#include "i2c.h"

#define dht11Pin 0
#define wait(t) os_delay_us(t * 1000UL)
#define uwait os_delay_us
#define read() pinRead(dht11Pin)

os_timer_t repeater;

void check() {
  dht_read();
  os_timer_arm(&repeater, 5000, 1);
}

void dht_read() {
  pinMode(dht11Pin, PinOpenDrain);

  // request
  pinWrite(dht11Pin, LOW);
  wait(20);
  pinWrite(dht11Pin, HIGH);
  uwait(45);

  // response
  if (!waitForResponse()) {
    os_printf("Failed to get ack response\n");
    return;
  }

  // read
  uint8_t dh1 = readByte();
  uint8_t dh2 = readByte();
  uint8_t dt1 = readByte();
  uint8_t dt2 = readByte();
  uint8_t checksum = readByte();

  if (dh1 + dh2 + dt1 + dt2 != checksum) {
    os_printf("Failed to check response!\n");
    os_printf("BYTES %d %d %d %d %d\n", dh1, dh2, dt1, dt2, checksum);
    return;
  }

  os_printf("H %d % TEMP %d C\n", dh1, dt1);
}

uint32_t waitForResponse() {
  uint32_t start = NOW();
  uint32_t timeout = start + 145;
  uint32_t count1 = 0;
  uint32_t count2 = 0;

  count1 = waitForState(HIGH, 60);
  count2 = waitForState(LOW, 85);

  return count1 > 0 && count2 > 0 ? true : false;
}

uint8_t readByte() {
  int bits = 7;
  uint8_t byte = 0;

  while(bits-- >= 0) {
    byte += readBit() << bits;
    os_delay_us(1);
  }

  return byte;
}

uint8_t readBit() {
  uint32_t state2;
  uint32_t state1 = waitForState(HIGH, 60);

  if (state1) {
    state2 = waitForState(LOW, 70);
    return state2 > state1 ? HIGH : LOW;
  }

  return LOW;
}

uint32_t waitForState(bool state, uint8_t duration) {
  uint32_t start = NOW();
  uint32_t timeout = start + duration;
  uint32_t counter = 0;

  while(true) {
    counter = NOW();

    if (read() == state) {
      return counter - start;
    }

    if (counter > timeout) {
      return 0;
    };
  }
}

void setup() {
  os_timer_setfn(&repeater, (os_timer_func_t*)check, NULL);
  os_timer_arm(&repeater, 5000, 1);
}

void loop() {}

#ifdef __cplusplus
}
#endif
