#ifdef __cplusplus
extern "C" {
#endif

#include "sdk.h"

#define WRITE_COMMAND           0x00
#define WRITE_DATA              0x40

#define SET_LOW_COLUMN          0x00
#define USE_EXTERNAL_VCC        0x01
#define USE_INTERNAL_VCC        0x02
#define SET_HIGH_COLUMN         0x10
#define SET_MEMORY_MODE         0x20
#define SET_COLUMN_ADDRESS      0x21
#define SET_PAGE_ADDRRESS       0x22
#define SET_FADE_BLINK          0x23
#define RIGHT_HSCROLL           0x26
#define LEFT_HSCROLL            0x27
#define RIGHT_DIAGSCROLL        0x29
#define LEFT_DIAGSCROLL         0x2a
#define DEACTIVATE_SCROLL       0x2e
#define ACTIVATE_SCROLL         0x2f
#define SET_START_LINE          0x40
#define SET_CONTRAST            0x81
#define CHARGE_PUMP             0x8D
#define X_MAP_NORMAL            0xA0
#define X_MAP_INVERTED          0xA1
#define SET_VSCROLL_AREA        0xA3
#define DISPLA_SHOW_MEMORY      0xA4
#define DISPLAY_ALL_ON          0xA5
#define NORMAL_DISPLAY          0xA6
#define INVERTED_DISPLAY        0xA7
#define SET_MULTIPLEX           0xA8
#define DISPLAY_OFF             0xAE
#define DISPLAY_ON              0xAF
#define PAGE_ADDRESSING_START   0xB0
#define COM_INCREMENTAL         0xC0
#define COM_DECREMENTAL         0xC8
#define SET_DISPLAY_OFFSET      0xD3
#define SET_CLOCK_DIVIDER       0xD5
#define SET_ZOOM                0xD6
#define SET_PRECHARGE           0xD9
#define SET_COM_PINS            0xDA
#define SET_VCOM_DETECT         0xDB
#define NOP                     0xE3

void loop();
void setup();

#ifdef __cplusplus
}
#endif
