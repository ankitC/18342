CC      = arm-linux-gcc
OBJCOPY = arm-linux-objcopy
CFLAGS  = -O2 -ffixed-r8 -ffreestanding -Wall -Werror -nostdinc \
          -I ../uboot/include -I include
LDFLAGS = -nostdlib -Wl,-e,$(ENTRY_SYMBOL),-N,-Ttext,$(LOAD_ADDR)

ENTRY_SYMBOL = main
LOAD_ADDR    = 0xa2000000

STUBS = ../uboot/stubs.o

objects = trial.o

default: trial.bin

.PHONY: default clean clobber

trial.bin: trial
	$(OBJCOPY) -O binary $< $@

trial: $(objects)
	$(CC) $(LDFLAGS) -o $@ $^ $(STUBS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f trial $(objects)

clobber: clean
	rm -f trial.bin
