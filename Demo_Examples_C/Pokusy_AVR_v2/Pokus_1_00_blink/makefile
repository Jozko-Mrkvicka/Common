CC = avr-gcc

# Override is only needed by avr-lib build system.
override CFLAGS = -g -Wall -O1 -mmcu=atmega8 $(DEFS)

all: hex

blink.elf: blink.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o blink.elf blink.hex

hex: blink.hex

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

load: blink.hex
	avrdude -p m8 -c AVRispmkII -P usb -U flash:w:$< 

