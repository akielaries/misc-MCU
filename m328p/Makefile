CC      = avr-gcc
MCU     = atmega328p
F_CPU   = 16000000UL
DEV     = /dev/ttyACM0
BAUD    = 115200
SRC     = blink_led3.c
OBJ     = $(SRC:.c=.o)
TARGET  = blink3

CFLAGS  = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS = -mmcu=$(MCU)

all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

upload: $(TARGET).hex
	sudo avrdude -F -V -D -c arduino -p $(MCU) -P $(DEV) -b $(BAUD) -U flash:w:$<

clean:
	rm -f *.o *.hex *.elf $(TARGET)

