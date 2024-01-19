CC = avr-gcc

MCU = atmega328p
F_CPU = 16000000UL

compile:
	$(CC) -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o blink2.o blink_led2.c
	$(CC) -mmcu=$(MCU) blink2.o -o blink2

objcpy:
	avr-objcopy -O ihex -R .eeprom blink2 blink2.hex

avrdude:
	sudo avrdude -F -V -D -c arduino -p $(MCU) -P /dev/ttyUSB0 -b 115200 -U flash:w:blink2.hex

clean:
	rm -f *.o *.hex blink2

