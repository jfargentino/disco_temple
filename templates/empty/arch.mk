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

# Toolchain ###################################################################
TOOLCHAIN ?= arm-none-eabi-
CC        := $(TOOLCHAIN)gcc
AS        := $(TOOLCHAIN)as
LD        := $(TOOLCHAIN)gcc
OBJCOPY   := $(TOOLCHAIN)objcopy
OBJDUMP   := $(TOOLCHAIN)objdump
STRIP     := $(TOOLCHAIN)strip
SIZE      := $(TOOLCHAIN)size

LD_SCRIPT ?= STM32F746NGHX_FLASH.ld

# Flags #######################################################################
MCPU := cortex-m7
MFPU := fpv5-sp-d16
PART := STM32F746xx

FLAGS := -mcpu=$(MCPU) -mthumb
FLAGS += -mfpu=$(MFPU) -mfloat-abi=hard

CFLAGS := $(FLAGS) -D$(PART)
CFLAGS += -std=gnu11 -Wall -pedantic
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -fstack-usage

LDFLAGS := $(FLAGS)
LDFLAGS += -specs=nosys.specs
#LDFLAGS += -specs=nano.specs
LDFLAGS += -Wl,--gc-sections
#LDFLAGS += -Wl,--start-group -lc -lm -Wl,--end-group

ASFLAGS := $(FLAGS)

