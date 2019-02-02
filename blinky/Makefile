ESPPORT 			?= /dev/ttyUSB0
FLASH_SPEED 	?= 230400

.PHONY: build flash erase clean

build:
	docker run --rm -ti -e VERBOSE=1 -e ESPPORT -v$$(pwd)/:/home/espbuilder/project --privileged espbuild

clean:
	rm -rf build/** firmware/**

erase:
	esptool.py --baud $(FLASH_SPEED) --port $(ESPPORT) erase_flash

flash:
	esptool.py --baud $(FLASH_SPEED) --port $(ESPPORT) write_flash -fm qio -fs 512KB 0x00000 firmware/0x00000.bin 0x10000 firmware/0x10000.bin 0x7c000 firmware/0x7c000.bin