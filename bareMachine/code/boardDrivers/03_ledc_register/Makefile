OBJS    := start.o led.o
LD      := arm-linux-gnueabihf-ld
GCC      := arm-linux-gnueabihf-gcc
OBJCOPY := arm-linux-gnueabihf-objcopy
OBJDUMP := arm-linux-gnueabihf-objdump

led.bin:$(OBJS)
	$(LD) -Timx6ull.lds -o ledc.elf $^
	$(OBJCOPY) -O binary -S ledc.elf $@
	$(OBJDUMP) -D -m arm ledc.elf > ledc.dis

%.o:%.s
	$(GCC) -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.S
	$(GCC) -Wall -nostdlib -c -O2 -o $@ $<
	
%.o:%.c
	$(GCC) -Wall -nostdlib -c -O2 -o $@ $<

.PHONY:clean

clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis
	