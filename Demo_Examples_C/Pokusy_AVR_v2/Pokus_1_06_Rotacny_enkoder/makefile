CC = avr-gcc

# Override is only needed by avr-lib build system.
override CFLAGS = -g -Wall -O1 -mmcu=atmega8

rebuild: clean all

all: pokus.hex

pokus.hex: pokus.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

pokus.elf: pokus.o
	$(CC) $(CFLAGS) -o $@ $^

pokus.o: pokus.c
	$(CC) $(CFLAGS) -o $@ -c $^

load: pokus.hex
	avrdude -p m8 -c AVRispmkII -P usb \
	-U lfuse:w:0xff:m \
	-U hfuse:w:0xd9:m \
	-U flash:w:$<:i

clean:
	rm -f *.o
	rm -f *.elf
	rm -f *.hex
