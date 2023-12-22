CC	= avr-gcc

compile:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega2560 -c -o blink2.o blink_led2.c
	avr-gcc -mmcu=atmega2560 blink2.o -o blink2

objcpy:
	avr-objcopy -O ihex -R .eeprom blink2 blink2.hex

avrdude:
	sudo avrdude -F -V -D -c wiring -p ATMEGA2560 -P /dev/ttyACM0 -b 115200 -U flash:w:blink2.hex

clean:
	rm -f *.o *.hex blink2
