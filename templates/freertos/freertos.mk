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

# FreeRTOS ####################################################################
FREERTOS_DIR   := Middlewares/Third_Party/FreeRTOS
FREERTOS_INC   := $(FREERTOS_DIR)/Source/include
PORTABLE_INC   := $(FREERTOS_DIR)/Source/portable/GCC/ARM_CM7/r0p1/
FREERTOS_SRC   := $(shell find $(FREERTOS_DIR) -name '*.c')
FREERTOS_SUB   := $(shell find $(FREERTOS_DIR) -type d)
FREERTOS_BUILD := $(addprefix $(BUILD)/, $(FREERTOS_SUB))
FREERTOS_OBJ   := $(addprefix $(BUILD)/, $(patsubst %.c, %.o, $(FREERTOS_SRC)))

$(FREERTOS_BUILD):
	mkdir -p $(FREERTOS_BUILD)

BUILD_TREE += $(FREERTOS_BUILD)
INCLUDE += -I$(FREERTOS_INC) -I$(PORTABLE_INC)
OBJ += $(FREERTOS_OBJ)

