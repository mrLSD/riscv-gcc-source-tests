run:
	@kflash -b 115200 -p /dev/ttyUSB0 -B goE -s -t .pio/build/sipeed-maixduino/firmware.elf
