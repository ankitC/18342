CC      = arm-linux-gcc
OBJCOPY = arm-linux-objcopy
AR		= arm-linux-ar
CFLAGS  = -O2 -ffixed-r8 -ffreestanding -Wall -Werror -nostdinc \
          -I ../uboot/include -I include -g
ASFLAGS = -nostdinc -I ../uboot/include -I include
LDFLAGS = -nostdlib -Wl,-N,-Ttext,$(LOAD_ADDR)

LOAD_ADDR = 0xa3000000

STUBS = ../uboot/stubs.o

objects = init.o dispatcher.o C_SWI_handler.o kernel.o

default: kernel.bin

.PHONY: default clean clobber

kernel.bin: kernel
	$(OBJCOPY) -O binary $< $@

kernel: start.o $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(STUBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) -S $(ASFLAGS) -o $@ $<	#TODO: confirm -S flag

clean:
	rm -f kernel start.o $(objects)

clobber: clean
	rm -f kernel.bin
