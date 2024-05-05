CROSS_COMPILE 	?= 
TARGET		  	?= queue

CC 				:= $(CROSS_COMPILE)gcc
OBJDUMP 		:= $(CROSS_COMPILE)objdump

LDFLAGS         := -lm
CFLAGS          := -Wall -O2

INCDIRS 		:= ./				   			   
SRCDIRS			:= ./
				   			   
INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))

CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))
CFILENDIR		:= $(notdir  $(CFILES))

COBJS			:= $(patsubst %, %, $(CFILENDIR:.c=.o))
OBJS			:= $(COBJS)

VPATH			:= $(SRCDIRS)

ifeq ("$(origin V)", "command line")
  KBUILD_VERBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 0
endif

ifeq ($(KBUILD_VERBOSE),1)
  Q =
else
  Q = @
endif

.PHONY: clean test
	
$(TARGET) : $(OBJS)
	$(Q)$(CC) $(CFLAGS) $(INCLUDE)  $(OBJS) -o $@ $(LDFLAGS)

$(COBJS) : %.o : %.c
	$(Q)$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@ $(LDFLAGS)
	
clean:
	rm -rf $(TARGET) $(COBJS)

test:
	echo $(OBJS) $(COBJS)
