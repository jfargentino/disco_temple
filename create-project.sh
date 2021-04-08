#!/bin/sh
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

# Environment #################################################################
. ./template.env

_template_check_env

# Inputs ######################################################################
if [ -z $2 ]; then
    TEMPLATE=$DEFAULT_TEMPLATE
else
    TEMPLATE=$2
fi
if [ -z $1 ]; then
    PROJECT=$TEMPLATE
else
    PROJECT=$1
fi

if [ -d "$WORKSPACE/$PROJECT" ]; then
    echo "\"$WORKSPACE/$PROJECT\" already exists, exiting"
    exit
fi
if [ ! -d "templates/$TEMPLATE" ]; then
    echo "template \"$TEMPLATE\" does not exist, exiting"
    exit
fi

echo "Creating \"$WORKSPACE/$PROJECT\" from template \"$TEMPLATE\"..."

# copy template ###############################################################
cp -rv templates/$TEMPLATE $WORKSPACE/$PROJECT

# copy board support pack #####################################################
mkdir -vp $WORKSPACE/$PROJECT/Drivers/BSP
cp -rv $REPO/Drivers/BSP/Components $WORKSPACE/$PROJECT/Drivers/BSP
cp -rv $REPO/Drivers/BSP/$BOARD $WORKSPACE/$PROJECT/Drivers/BSP

# copy CMSIS ##################################################################
mkdir -vp $WORKSPACE/$PROJECT/Drivers/CMSIS/Device/ST/STM32F7xx/Include
cp -rv $REPO/Drivers/CMSIS/Include $WORKSPACE/$PROJECT/Drivers/CMSIS/
cp -v $REPO/Drivers/CMSIS/Device/ST/STM32F7xx/Include/stm32f7xx.h \
       $WORKSPACE/$PROJECT/Drivers/CMSIS/Device/ST/STM32F7xx/Include
cp -v $REPO/Drivers/CMSIS/Device/ST/STM32F7xx/Include/system_stm32f7xx.h \
       $WORKSPACE/$PROJECT/Drivers/CMSIS/Device/ST/STM32F7xx/Include
cp -v $REPO/Drivers/CMSIS/Device/ST/STM32F7xx/Include/$DEV.h \
       $WORKSPACE/$PROJECT/Drivers/CMSIS/Device/ST/STM32F7xx/Include
rm -rvf $WORKSPACE/$PROJECT/Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates
rm -rvf $WORKSPACE/$PROJECT/Drivers/CMSIS/DSP_Lib
rm -rvf $WORKSPACE/$PROJECT/Drivers/CMSIS/RTOS
rm -rvf $WORKSPACE/$PROJECT/Drivers/CMSIS/RTOS2

# copy HAL ####################################################################
mkdir -vp $WORKSPACE/$PROJECT/Drivers/STM32F7xx_HAL_Driver
cp -rv $REPO/Drivers/STM32F7xx_HAL_Driver/Inc \
       $WORKSPACE/$PROJECT/Drivers/STM32F7xx_HAL_Driver
cp -rv $REPO/Drivers/STM32F7xx_HAL_Driver/Src \
       $WORKSPACE/$PROJECT/Drivers/STM32F7xx_HAL_Driver
rm -v $WORKSPACE/$PROJECT/Drivers/STM32F7xx_HAL_Driver/Inc/*_template.h
rm -rvf $WORKSPACE/$PROJECT/Drivers/STM32F7xx_HAL_Driver/Src/Legacy
rm -v $WORKSPACE/$PROJECT/Drivers/STM32F7xx_HAL_Driver/Src/*_template.c

# copy Utilities ##############################################################
mkdir -vp $WORKSPACE/$PROJECT/Utilities
cp -rv $REPO/Utilities/CPU $WORKSPACE/$PROJECT/Utilities
cp -rv $REPO/Utilities/Fonts $WORKSPACE/$PROJECT/Utilities
cp -rv $REPO/Utilities/JPEG $WORKSPACE/$PROJECT/Utilities
cp -rv $REPO/Utilities/Log $WORKSPACE/$PROJECT/Utilities

THIRD_PART=Middlewares/Third_Party

# copy FreeRTOS ###############################################################
if [ $FREERTOS -gt 0 ]; then
    L_FREERTOS=$WORKSPACE/$PROJECT/$THIRD_PART/FreeRTOS/
    mkdir -vp $L_FREERTOS/Source
    R_FREERTOS=$REPO/$THIRD_PART/FreeRTOS/
    cp -rv $R_FREERTOS/License $L_FREERTOS/
    #cp -rv $R_FREERTOS/Source/CMSIS_RTOS_V2 $L_FREERTOS/Source
    cp -rv $R_FREERTOS/Source/CMSIS_RTOS $L_FREERTOS/Source
    cp -rv $R_FREERTOS/Source/include $L_FREERTOS/Source
    rm -v $L_FREERTOS/Source/include/*_template.h
    cp -rv $R_FREERTOS/Source/*.c $L_FREERTOS/Source
    # portable depends on MPU
    mkdir -vp $L_FREERTOS/Source/portable/GCC
    if [ $MPU -gt 0 ]; then
        cp -rv $R_FREERTOS/Source/portable/Common $L_FREERTOS/Source/portable/
        cp -rv $R_FREERTOS/Source/portable/GCC/ARM_CM7_MPU $L_FREERTOS/Source/portable/GCC/
    else
        cp -rv $R_FREERTOS/Source/portable/GCC/ARM_CM7 $L_FREERTOS/Source/portable/GCC/
    fi
    # memory man
    if [ $MEM -gt 0 ]; then
        mkdir -vp $L_FREERTOS/Source/portable/MemMang
        cp -v $R_FREERTOS/Source/portable/MemMang/heap_$MEM.c $L_FREERTOS/Source/portable/MemMang/
    fi
    cp -v templates/freertos/Core/Inc/FreeRTOSConfig.h $WORKSPACE/$PROJECT/Core/Inc
    cp -v templates/freertos/freertos.mk $WORKSPACE/$PROJECT/
fi

# copy LVGL ###################################################################
if [ $LVGL -gt 0 ]; then
    mkdir -p $WORKSPACE/$PROJECT/$THIRD_PART/
    L_LVGL=$WORKSPACE/$PROJECT/$THIRD_PART/lvgl
    R_LVGL=./$THIRD_PART/lvgl-7.11.0
    cp -rv $R_LVGL $L_LVGL
    cp -rv ./Drivers/SDL $WORKSPACE/$PROJECT/Drivers
    cp -rv templates/lvgl/Core/ $WORKSPACE/$PROJECT/
    cp -v templates/lvgl/*.mk $WORKSPACE/$PROJECT/
    cp -v templates/lvgl/Makefile.* $WORKSPACE/$PROJECT/
    cp -v templates/lvgl/.cproject $WORKSPACE/$PROJECT/
fi

# substitute the project name #################################################
_template_rename() {
    SRC=$1
    DST=`echo $SRC | sed "s/NAME_TO_SUBSTITUTE_BY_TEMPLATE/$2/g"`
    mv $SRC $DST
}

find $WORKSPACE/$PROJECT -type f \
         -exec sed -i "s/NAME_TO_SUBSTITUTE_BY_TEMPLATE/$PROJECT/g" '{}' \;
find $WORKSPACE/$PROJECT -type f -name "*NAME_TO_SUBSTITUTE_BY_TEMPLATE*" | \
    while read f; do _template_rename $f $PROJECT; done

