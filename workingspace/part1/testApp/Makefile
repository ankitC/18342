CC      = arm-linux-gcc
OBJCOPY = arm-linux-objcopy
CFLAGS  = -O0 -ffreestanding -Wall -Werror -nostdinc -I ../libc/include
LDFLAGS = -nostdlib -Wl,-Ttext,$(LOAD_ADDR) 

LOAD_ADDR = 0xa2000000

CRT0    = ../libc/crt0.o
LDLIBS  = ../libc/libc.a

objects = testApp.o

default: testApp.bin

.PHONY: default clean clobber

testApp.bin: testApp
	$(OBJCOPY) -O binary $< $@

testApp: $(objects)
	$(CC) $(LDFLAGS) -o $@ $(CRT0) $^ $(LDLIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f testApp $(objects)

clobber: clean
	rm -f testApp.bin
