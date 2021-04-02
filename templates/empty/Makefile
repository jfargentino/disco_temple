##
#    Copyright 2021 ENEGENO
# 
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
# 
#       http://www.apache.org/licenses/LICENSE-2.0
# 
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
# 
##

# executable name #############################################################
PRODUCT_NAME := NAME_TO_SUBSTITUTE_BY_TEMPLATE

# Build config: Debug or Release ##############################################
# as with eclipse based tools, the build tree root is different  
DEBUG ?= 1

# toolchain and flags definitions #############################################
include arch.mk

# Define build inputs and outputs #############################################

# Build tree
ifeq ($(DEBUG), 1)
	BUILD := Debug
else
	BUILD := Release
endif

# end products (executable, asm listing...)
PRODUCT_BASE  := $(BUILD)/$(PRODUCT_NAME)
PRODUCT_TMP   := $(PRODUCT_BASE).tmp
PRODUCT_ELF   := $(PRODUCT_BASE).elf
PRODUCT_HEX   := $(patsubst %.elf,%.hex,$(PRODUCT_ELF))
PRODUCT_BIN   := $(patsubst %.elf,%.bin,$(PRODUCT_ELF))
PRODUCT_MAP   := $(patsubst %.elf,%.map,$(PRODUCT_ELF))
PRODUCT_LIST  := $(patsubst %.elf,%.list,$(PRODUCT_ELF))
DEBUG_SYMBOLS := $(PRODUCT_BASE).debug

# default target builds dependencies too (det target)
all: $(PRODUCT_ELF) $(PRODUCT_HEX) $(PRODUCT_BIN) $(PRODUCT_LIST) dep tags
	$(SIZE) $(PRODUCT_ELF)

# sub-makefiles inclusions ####################################################
# before to include any sub-makefiles, we initialize the variables they would
# update:
#    - BUILD_TREE: the build subdirectories
#    - INCLUDE: the include pathes
#    - OBJ: the object files to be built

# as with eclipse based tools, the build tree is similar to the source one
# every sub-makefiles should append its build subtree in BUILD_TREE
BUILD_TREE := $(BUILD)

# starts with an empty include path and empty object file list
INCLUDE :=
OBJ :=

# CMSIS: updates INCLUDE only
include cmsis.mk

# HAL: updates BUILD_TREE, INCLUDE and OBJ
include hal.mk

# BSP: updates BUILD_TREE, INCLUDE and OBJ
# Must be edited depending on what part of the BSP you want to compile,
# this one differ from the others since it does not compile all its source,
include bsp.mk

# FreeRTOS: updates BUILD_TREE, INCLUDE and OBJ
# optional
-include freertos.mk

# LVGL: updates BUILD_TREE, INCLUDE and OBJ
#       adds -DSTM32F7 to CFLAGS to enable DMA2D
# optional
-include lvgl.mk

# User src: updates BUILD_TREE, INCLUDE and OBJ,
#           defines PROJ_INC, headers wich trig a rebuild
include core.mk

# Targets #####################################################################
CFLAGS += -DPRODUCT_NAME=\"$(PRODUCT_NAME)\"

# the stack usage files (*.su) are generated thanks to cflags "-stack-usage" 
$(BUILD)/%.o: %.c $(PROJ_INC)
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

# dependencies (TODO -MM ?)
$(BUILD)/%.d: %.c $(PROJ_INC)
	$(CC) $(INCLUDE) $(CFLAGS) -M $< > $@

$(BUILD)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD)/%.d: %.s
	$(CC) $(INCLUDE) $(CFLAGS) -M $< > $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

# asm listing
%.list: %.elf
	$(OBJDUMP) -h -S $< > $@

$(PRODUCT_ELF): $(PRODUCT_TMP) $(DEBUG_SYMBOLS)
	cp $(PRODUCT_TMP) $(PRODUCT_ELF)
	$(STRIP) --strip-debug --strip-unneeded $(PRODUCT_ELF)
	$(OBJCOPY) --add-gnu-debuglink=$(DEBUG_SYMBOLS) $(PRODUCT_ELF)

$(DEBUG_SYMBOLS): $(PRODUCT_TMP)
	$(OBJCOPY) --only-keep-debug $< $@

$(PRODUCT_TMP): obj
	$(LD) -T $(LD_SCRIPT) $(LDFLAGS) -Wl,-Map=$(PRODUCT_MAP) -o $@ $(OBJ)

# build tree
$(BUILD_TREE):
	mkdir -p $@

# build object files
obj: $(BUILD_TREE) $(OBJ)

# dependcy files are alonside the object, "*.d" extension
DEP := $(patsubst %.o, %.d, $(OBJ))

# build depency files
dep: $(BUILD_TREE) $(DEP) $(BUILD)/compiler.def

$(BUILD)/compiler.def:
	$(CC) $(CFLAGS) -E -dM - < /dev/null > $@

# stack usage files are alonside the object, "*.su" extension
STU := $(patsubst %.o, %.su, $(OBJ))

# TODO vpath %.c $(HAL_DIR)/Src $(BSP_DIR)

tags: $(PROJ_SRC) $(PROJ_INC)
	ctags -R .

# FLASH and DBG ###############################################################
# TODO
dbgserver:
	/path/to/STLinkST-LINK_gdbserver.sh -c /path/to/stm32f746g-disco_config.txt

# TODO load in flash/ram, TUI, batch mode the run nemiver
dbg: $(PRODUCT_ELF)
	arm-none-eabi-gdb -x gdbinit $(PRODUCT_ELF)

# Cleaning ####################################################################
clean:
	-@rm -vf $(OBJ) $(PRODUCT_TMP)

distclean: clean
	-@rm -vf $(DEP) $(STU) $(DEBUG_SYMBOLS) tags
	-@rm -vf $(PRODUCT_BIN) $(PRODUCT_ELF) $(PRODUCT_HEX)
	-@rm -vf $(PRODUCT_MAP) $(PRODUCT_LIST) $(BUILD)/compiler.def

erase: clean distclean
	-rm -rvf $(BUILD) Debug Release

.PHONY: obj dep clean distclean erase all

