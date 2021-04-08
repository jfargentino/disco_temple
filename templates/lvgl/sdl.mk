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

SDL_SRC := Core/Src/lv_demo_widgets.c
SDL_SRC += Core/Sdl/mouse_cursor_icon.c
SDL_SRC += Core/Sdl/main.c

BUILD_TREE += $(BUILD)/Core/Src/ $(BUILD)/Core/Sdl/

SDL_OBJ := $(patsubst %.c, %.o, $(addprefix $(BUILD)/, $(SDL_SRC)))
OBJ += $(SDL_OBJ)

INCLUDE += -ICore/Inc -ICore/Sdl
