FLASH_SPEED   ?= 230400
ESP_PORT      ?= $$(ls /dev/tty.wchusbserial*)

.PHONY: build flash

build:
	docker run --rm -it -v$$(pwd)/:/home/espbuilder/project -v/Users/dizzypotato/labs/@homebots/ESP8266_NONOS_SDK:/home/espbuilder/esp-open-sdk/sdk darlanalves/homebots-sdk:latest

flash:
	esptool.py --baud $(FLASH_SPEED) --port $(ESP_PORT) write_flash -fm qio -fs 512KB 0x00000 firmware/0x00000.bin 0x10000 firmware/0x10000.bin 0x7c000 firmware/0x7c000.bin

