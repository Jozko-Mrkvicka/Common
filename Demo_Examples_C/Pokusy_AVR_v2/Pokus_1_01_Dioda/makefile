all: dioda.hex

dioda.o: dioda.c
	avr-gcc -Wall -mmcu=atmega8 -o $@ -c $<

dioda.elf: dioda.o
	avr-gcc -o $@ $<

dioda.hex: dioda.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

# nastavenie fuse bits
# -U lfuse:w:0xff:m -U hfuse:w:0xd9:m  ->  externy 4MHz krystal
load: dioda.hex
	avrdude -p m8 -c AVRispmkII -P usb \
	-U lfuse:w:0x00:m \
	-U hfuse:w:0xd9:m \
	-U flash:w:dioda.hex:i 

clean:
	rm -f *.o *.elf *.hex
