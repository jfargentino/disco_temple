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
TOOLCHAIN ?=
CC        := $(TOOLCHAIN)gcc
AS        := $(TOOLCHAIN)as
LD        := $(TOOLCHAIN)gcc
OBJCOPY   := $(TOOLCHAIN)objcopy
OBJDUMP   := $(TOOLCHAIN)objdump
STRIP     := $(TOOLCHAIN)strip
SIZE      := $(TOOLCHAIN)size

# Flags #######################################################################
WFLAGS := -Wall -Wextra -pedantic
WFLAGS += -Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes
WFLAGS += -Wno-discarded-qualifiers -Wno-error=strict-prototypes
WFLAGS += -Wtype-limits -Wsizeof-pointer-memaccess -Wpointer-arith
WFLAGS += -Wempty-body -Wshift-negative-value -Wstack-usage=2048 -Wreturn-type
WFLAGS += -Wmultichar -Wformat-security -Wdouble-promotion -Wclobbered
WFLAGS += -Wdeprecated -Wuninitialized

CFLAGS := -std=gnu11 $(WFLAGS)
CFLAGS += -DSDL_BUILD -DLV_CONF_INCLUDE_SIMPLE -DLV_LVGL_H_INCLUDE_SIMPLE

LDFLAGS := -lSDL2 -lm

