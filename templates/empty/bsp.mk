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

# BSP Features; remove any you don't need
BSP := audio camera eeprom lcd qspi sd sdram ts

# BSP #########################################################################
BSP_DIR   := Drivers/BSP/STM32746G-Discovery
BSP_INC   := $(BSP_DIR)
BSP_SRC   := $(BSP_DIR)/stm32746g_discovery.c
BSP_SRC   += $(addsuffix .c, $(addprefix $(BSP_DIR)/stm32746g_discovery_, $(BSP)))
BSP_BUILD := $(addprefix $(BUILD)/, $(BSP_DIR))
BSP_OBJ   := $(addprefix $(BUILD)/, $(patsubst %.c, %.o, $(BSP_SRC)))

BUILD_TREE += $(BSP_BUILD)
INCLUDE += -I$(BSP_INC)
OBJ += $(BSP_OBJ)
