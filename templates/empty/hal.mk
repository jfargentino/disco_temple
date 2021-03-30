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

# HAL #########################################################################
HAL_DIR   := Drivers/STM32F7xx_HAL_Driver
HAL_INC   := $(HAL_DIR)/Inc
HAL_SRC   := $(shell find $(HAL_DIR)/Src -name '*.c')
HAL_BUILD := $(addprefix $(BUILD)/, $(HAL_DIR)/Src)
HAL_OBJ   := $(addprefix $(BUILD)/, $(patsubst %.c, %.o, $(HAL_SRC)))

BUILD_TREE += $(HAL_BUILD)
INCLUDE += -I$(HAL_INC)
OBJ += $(HAL_OBJ)

