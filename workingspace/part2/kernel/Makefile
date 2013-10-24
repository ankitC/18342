CC      = arm-linux-gcc
OBJCOPY = arm-linux-objcopy
AR		= arm-linux-ar
CFLAGS  = -O0 -g -ffixed-r8 -ffreestanding -Wall -Werror -nostdinc \
          -I ../uboot/include -I include 
ASFLAGS = -nostdinc -I ../uboot/include -I include
LDFLAGS = -nostdlib -Wl,-N,-Ttext,$(LOAD_ADDR)

LOAD_ADDR = 0xa3000000

STUBS = ../uboot/stubs.o

objects = init.o dispatcher.o restore_old_SWI.o C_SWI_handler.o exit_to_kernel.o kernel.o

default: kernel.bin

.PHONY: default clean clobber

kernel.bin: kernel
	$(OBJCOPY) -O binary $< $@

kernel: start.o $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(STUBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) -c $(ASFLAGS) -o $@ $<


clean:
	rm -f kernel start.o $(objects)

clobber: clean
	rm -f kernel.bin
