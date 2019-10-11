#ifdef __cplusplus
extern "C" {
#endif

#include "sdk.h"

void loop();
void setup();

void dht_read();
uint8_t readBit();
uint8_t readByte();
uint32_t waitForResponse();
uint32_t waitForState(bool state, uint8_t duration);

#ifdef __cplusplus
}
#endif
