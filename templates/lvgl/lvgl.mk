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

# LVGL ########################################################################
LVGL_DIR   := Middlewares/Third_Party/lvgl
LVGL_INC   := $(LVGL_DIR)/src
LVGL_SRC   := $(shell find $(LVGL_DIR) -name '*.c')
LVGL_SUB   := $(shell find $(LVGL_DIR) -type d)
LVGL_BUILD := $(addprefix $(BUILD)/, $(LVGL_SUB))
LVGL_OBJ   := $(addprefix $(BUILD)/, $(patsubst %.c, %.o, $(LVGL_SRC)))

# to avoid warning lv_gpu/lv_gpu_stm32_dma2d.c line 71:
#"LVGL can't enable the clock of DMA2D"
CFLAGS += -DSTM32F7

BUILD_TREE += $(LVGL_BUILD)
INCLUDE += -I$(LVGL_INC)
OBJ += $(LVGL_OBJ)

