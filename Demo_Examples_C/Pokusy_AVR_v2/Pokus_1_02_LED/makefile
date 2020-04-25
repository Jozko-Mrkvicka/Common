
# Override is only needed by avr-lib build system.
# override CFLAGS = -g -Wall -O1 -mmcu=atmega8 $(DEFS)


# all: 





# avr-objcopy -j .text -j .data -O ihex led.elf led.hex

# avrdude -p m8 -c avrispmkii -P usb -U flash:w:led.hex:i

# load:

# CFLAGS = -I -Wall

# led.elf: led.o
#  	avr-gcc -mmcu=atmega8 -o led.elf led.o


# led.o: led.c
# 	avr-gcc -mmcu=atmega8 -o led.o -c led.c




# led.hex: 
# 	avr-objcopy -j .text -j .data -O ihex led.elf led.hex


# CC = avr-gcc

# Override is only needed by avr-lib build system.
# override CFLAGS = -Wall -mmcu=atmega8

# all: hex
# all: led.hex
all: led.hex

led.o: led.c
	avr-gcc -Wall -mmcu=atmega8 -o led.o -c led.c

led.elf: led.o
	avr-gcc -o led.elf led.o

led.hex: led.elf
	avr-objcopy -j .text -j .data -O ihex led.elf led.hex

load: led.hex
	avrdude -p m8 -c AVRispmkII -P usb -U flash:w:led.hex:i 

clean:
	rm -f *.o *.elf *.hex
