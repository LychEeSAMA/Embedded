CROSS_COMPILER  ?= 

TARGET		    ?= chr_list
BUILD_DIR	    ?= obj
TARGET_DIR      ?= bin

CC				?= $(CROSS_COMPILER)gcc
LD				?= $(CROSS_COMPILER)ld
OBJCOPY			?= $(CROSS_COMPILER)objcopy
OBJDUMP			?= $(CROSS_COMPILER)objdump
CXX 			?= $(CROSS_COMPILER)g++
CPP             ?= $(CROSS_COMPILER)gcc
AS				?= $(CROSS_COMPILER)as
GDB				?= $(CROSS_COMPILER)gdb
STRIP			?= $(CROSS_COMPILER)strip
AR				?= $(CROSS_COMPILER)ar
NM				?= $(CROSS_COMPILER)nm

LIBPATH			:= -lgcc -lm -lfreetype -L ./lib
INCLUDE			:= ./include/freetype2/freetype/ \
				   ./include/freetype2/freetype/config \
				   ././include/freetype2

CFILES			=	$(wildcard ./src/*.c) \

LOCAL_CFLAGS 	:= -std=c11 
LOCAL_CFLAGS 	+= -O3
LOCAL_CFLAGS 	+= -Wall -Wextra
LOCAL_CFLAGS 	+= -DWITH_FS_RES 
LOCAL_CFLAGS 	+= -Wno-unused-variable 
LOCAL_CFLAGS 	+= -Wno-unused-parameter 
LOCAL_CFLAGS 	+= -Wno-unused-function 
LOCAL_CFLAGS 	+= -Wno-unused-result
LOCAL_CFLAGS 	+= -Wno-int-to-pointer-cast
LOCAL_CFLAGS 	+= -Wno-incompatible-pointer-types
LOCAL_CFLAGS 	+= -Wno-implicit-function-declaration
LOCAL_CFLAGS    += -fexec-charset=UTF-8
LOCAL_CFLAGS    += -finput-charset=UTF-8 
LOCAL_SFLAGS    := -O0

COBJS			:=	$(patsubst %.c, $(BUILD_DIR)/%.o,$(notdir $(CFILES)))
SOBJS_1			:=	$(notdir $(SFILES:.s=.o))
SOBJS_2			:=	$(notdir $(SOBJS_1:.S=.o))
SOBJS			:=	$(patsubst %.o, $(BUILD_DIR)/%.o, $(SOBJS_2))
IINCLUDE		:= 	$(addprefix -I,$(INCLUDE))

SILENT_CPP  = @echo "CPP	$<";
SILENT_CC   = @echo "CC 	$<";
SILENT_S    = @echo "S  	$<";
SILENT_GCH  = @echo "GCH	$<";
SILENT_MM   = @echo "MM 	$<";
SILENT_AR   = @echo "AR 	$<";
SILENT_LD   = @echo "LD 	$<";

ifeq ("v", $(findstring s,$(MAKEFLAGS)))
Q = 
else
Q = $(SILENT_CC)
endif

GREEN   := \e[1;32m
NC      := \e[0m

vpath %.c $(dir $(CFILES))

$(TARGET_DIR)/$(TARGET) : $(COBJS) 
	$(Q) $(CC) $^ $(LOCAL_CFLAGS) $(IINCLUDE) $(LIBPATH)  -o $@ 
	$(Q) $(OBJDUMP) -d $@ > $@.dis

$(BUILD_DIR)/%.o : %.c
	$(Q) $(CC) $(IINCLUDE) -MMD -MP -MF"$(@:%.o=%.d)" $(LOCAL_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o : %.s
	$(Q) $(CC) -Wall $(LOCAL_SFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o : %.S
	$(Q) $(CC) -Wall $(LOCAL_SFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean 


CLEAN_TYPE 	?= *.o *.bin *.elf *.dis *.d

clean:
	@rm -rf $(addprefix $(BUILD_DIR)/,$(CLEAN_TYPE))
	@rm -rf $(TARGET_DIR)/$(TARGET)*

print:
	@echo COBJS: $(COBJS)
	@echo sOBJS: $(SOBJS)
	@echo CFILES: $(CFILES)
	@echo Q: $(Q)
	@echo CFILES: $(CFILES)

all : clean $(BUILD_DIR) $(TARGET_DIR)/$(TARGET) 
	@echo "$(GREEN)build [$(TARGET)] finised at `date +"%Y-%m-%d %H:%M:%S"`$(NC)"

# auto add head-files dependencies.
-include $(BUILD_DIR)/*.d 