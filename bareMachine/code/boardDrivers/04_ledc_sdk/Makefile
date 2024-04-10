CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET        ?= ledc

LD            := $(CROSS_COMPILE)ld
CC            := $(CROSS_COMPILE)gcc
OBJCOPY       := $(CROSS_COMPILE)objcopy
OBJDUMP       := $(CROSS_COMPILE)objdump

OBJS    := start.o led.o

$(TARGET).bin:$(OBJS)
	$(LD) -Timx6ull.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

%.o:%.s
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.S
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.c
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<


.PHONY:clean

clean:
	rm -rf *.o $(TARGET).bin $(TARGET).elf $(TARGET).dis
