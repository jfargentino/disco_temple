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

# Project sources and sub-directories #########################################
PROJ_SRC   := $(shell find Core -name '*.c' -or -name '*.s')
PROJ_SUB   := $(shell find Core -type d)
PROJ_BUILD := $(addprefix $(BUILD)/, $(PROJ_SUB))
PROJ_OBJ   := $(addprefix $(BUILD)/, $(patsubst %.c, %.o, $(PROJ_SRC)))
# do not forget there is an asm file
PROJ_OBJ   := $(patsubst %.s, %.o, $(PROJ_OBJ))

PROJ_INC   := $(shell find Core/Inc -name '*.h')

BUILD_TREE += $(PROJ_BUILD)
INCLUDE += -ICore/Inc
OBJ += $(PROJ_OBJ)

