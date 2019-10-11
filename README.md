## ESP8266 examples

Source code examples for [docker-espbuild](https://github.com/homebots/docker-espbuild)

- [Blinky](https://github.com/homebots/esp8266-starter-examples/tree/master/blinky)

### How to flash

Don't forget to install `esptool.py` if you don't have it yet.

You also need Docker to build the project.

### Build and flash

Put your ESP8266 in flash mode, go to your terminal and try the following im a terminal:

```
$ make build
$ make flash
```

The first command will compile a sketch with Docker.
The second command will try to find a port at `/dev/tty.wchusbserial14*` and flash to that port
All scripts are based on a CH340G USB/serial connector
