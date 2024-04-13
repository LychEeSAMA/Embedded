CROSS_COMPILE 	?= arm-linux-gnueabihf-
TARGET		  	?= keyFilter

CC 				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld
OBJCOPY 		:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump

INCDIRS 		:= imx6ul \
				   bsp/clk \
				   bsp/led \
				   bsp/delay \
				   bsp/beep \
				   bsp/key \
				   bsp/gpio \
				   bsp/exti \
				   bsp/interrput \
				   bsp/epitTimer \
				   bsp/keyFilter
				   			   
SRCDIRS			:= project \
				   bsp/clk \
				   bsp/led \
				   bsp/delay \
				   bsp/beep \
				   bsp/key \
				   bsp/gpio \
				   bsp/exti \
				   bsp/interrput \
				   bsp/epitTimer \
				   bsp/keyFilter

				   			   
INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))

#获取SRCDIRS文件夹中.c和.s的路径 结果如：project/start.s
SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
#获取SRCDIRS文件夹中.c和.s的路径 结果如：bsp/clk/clock.c
CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

#获取所有.c .s文件的文件名称 project/start.s-->start.s
SFILENDIR		:= $(notdir  $(SFILES))
CFILENDIR		:= $(notdir  $(CFILES))

#将所有源文件名称的后缀全变变成.o 并在其前加上前缀obj
SOBJS			:= $(patsubst %, obj/%, $(SFILENDIR:.S=.o))
COBJS			:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))
OBJS			:= $(SOBJS) $(COBJS)

#设置make时寻找编译文件的路径
VPATH			:= $(SRCDIRS)

.PHONY: clean
	
$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

#静态模式 将所有.s编译出来的.o放到obj目录下去
$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -c -O2  $(INCLUDE) -o $@ $<

#静态模式 将所有.c编译出来的.o放到obj目录下去
$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2  $(INCLUDE) -o $@ $<
	
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)

	
