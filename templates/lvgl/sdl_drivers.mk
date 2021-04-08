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

DRIVERS_DIR := Drivers/SDL/

INCLUDE += -I$(DRIVERS_DIR)

DRIVERS_SRC := $(wildcard $(DRIVERS_DIR)/display/*.c)
DRIVERS_SRC += $(wildcard $(DRIVERS_DIR)/gtkdrv/*.c)
DRIVERS_SRC += $(wildcard $(DRIVERS_DIR)/indev/*.c)

BUILD_TREE += $(BUILD)/$(DRIVERS_DIR)/display/
BUILD_TREE += $(BUILD)/$(DRIVERS_DIR)/gtkdrv/
BUILD_TREE += $(BUILD)/$(DRIVERS_DIR)/indev/
BUILD_TREE += $(BUILD)/$(DRIVERS_DIR)/wayland/

DRIVERS_OBJ := $(patsubst %.c, %.o, $(addprefix $(BUILD)/, $(DRIVERS_SRC)))
OBJ += $(DRIVERS_OBJ)
