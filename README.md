# DISCO TEMPLE

This is a workspace for developing with the [STM32F746G-DISCO](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html) evaluation kit, providing a Makefile-based project supporting the HAL and CMSIS layers, plus per-peripheral BSP configuration.

The source layout is similar to a `STM32CubeIDE` project generated from a `STM32CubeMX` configuration, even the build pathes are the same. The [`.project`](./templates/empty/.project), [`.settings/*`](./templates/empty/.settings/), and [`.cproject`](./templates/empty/.cproject) files are there thus you can open it in `STM32CubeIDE`, thanks to "File/Open Projects from File System..."

It's done to document how to set-up a project from scratch, because there is no STM32CubeMx nor STM32CubeIDE examples to start
with. And starting a project with STM32CubeMx is a frustrating experience for new comers: empty project won't toggle LED1 as intended, you have to understand the HAL/CMSIS/BSP sandwich, comparing projects is difficult...

---

## Layout

  * [`Middlewares`](./Middlewares/): for `Third_Party/lvgl` only (TODO).
  * [`templates`](./templates/): pristine project templates.
  * [`template.env`](./template.env): you must update it with your STM32CubeIDE workspace, the FW source repo...
  * [`create-project.sh`](./create-project.sh): creates a new project in the STM32CubeIDE workspace from a template.
  * [`create-patch.sh`](./create-patch.sh): creates a patch set between a template and a project.

---

## Needs

  1. Install an ARM toolchain. I'm using [Canonical's](https://launchpad.net/gcc-arm-embedded) (they provide builds for Linux, OS X and Windows).
  2. Install a GDB server: [stlink](https://github.com/texane/stlink), [OpenOCD](http://openocd.org/), others ?
  3. Install [STM32F7 Cube Package](https://www.st.com/en/embedded-software/stm32cubef7.html), update [`template.env`](./template.env) with the path of the installed sources, probably `~/STM32Cube/Repository/STM32Cube_FW_F7_Vx.y.z`.

Steps 1 and 2 are not necessary in case you want to use [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) only.

Build with `arm-none-eabi-9-2020-q2-update` and `STM32CubeIDE 1.6.0 9614_20210223_1703(UTC)`.
Under UBUNTU 18.04 and 20.04, Windows 10.

TODO: not all combination tested yet, WSL.

---

## Building a test project

  1. Check [`template.env`](./template.env) for revelant configuration
  2. Create a template based project with [`create-project.sh`](./create-project.sh) script
  3. Build with `make` or `STM32CubeIDE`

For now, only one [template](./templates/empty/), with or without [FreeRTOS](./templates/freertos/).

[`create_patch.sh`](./create-patch.sh) generates patches to recreate your project from a brand new one.

*ACHTUNG* ! It temporary moves the project, and call "`make erase`" in it !

*DO NOT BLINDLY APPLY THEM ON A TEMPLATE* !
You still have to handle the project name where it appears, or if a file name contains the project name, you have to change the patch accordingly.

---

## Debug

A GDB server that connects to the ST-Link, one of the following:

  * [ST-LINK GDB server](./dbg_ressources/ST-LINK_gdbserver/), only for ST-Link, distributed with `STM32CubeIDE`.
  * it's open source [clone](https://github.com/stlink-org/stlink), available from ubuntu 20.04 repo.
  * [OpenOCD](http://openocd.org/), source code [there](git://git.code.sf.net/p/openocd/code
), version from ubuntu 20.04 repo should support ST-Link and STM32F7xx (SWV ?).

Revelant configuration for ST-LINK GDB server can be found in [this file](./dbg_ressources/ST-LINK_gdbserver/stm32f746g-disco_config.txt), alongside a [script](./dbg_ressources/ST-LINK_gdbserver/ST-LINK_gdbserver.sh). A real installation is still needed, at least for flashing process wich call XYZ (hardcoded).

A GDB client connects to the server through a TCP connection, all tested solution are based on `arm-none-eabi-gdb`. The command to load and start the debug session can be found in [this file](./templates/empty/gdbinit).

In addition to the TUI mode, two GUIs are evaluated: `STM32CubeIDE` and [`Nemiver`](https://wiki.gnome.org/Apps/Nemiver).

TODO: hard to use SWO outside STM32CubeIDE, trying [Eclipse Standalone Debugger](https://wiki.eclipse.org/CDT/StandaloneDebugger) and [gdbgui](https://github.com/cs01/gdbgui/)

---

## Simple project discovery

We will try to write and modify code in the [Core directory](./templates/empty/Core/) _ONLY_.

  * the [startup code](./templates/empty/Core/Startup/startup_stm32f746nghx.s), should not change that much, just maybe the vector table to update with the IRQ handler name you've changed. These are declared as weak symbols.
  * the [HAL configuration header](./templates/empty/Core/Inc/stm32f7xx_hal_conf.h) where you enable/disable BSP modules, set the clocks speeds with HSE/HSI and LSE/LSI. Other revelant configurations are:
    - `TICK_INT_PRIORITY`.
    - `USE_RTOS`.
    - `USE_HAL_XYZ_REGISTER_CALLBACKS`.
    - `USE_FULL_ASSERT` and the `assert_param` macro definition.
    - MAC/PHY address and other ETH relative config.
  * the [HAL initialization code](./templates/empty/Core/Src/stm32f7xx_hal_msp.c) (what MSP and PPP stand for ?)
  * the [IRQ handlers](./templates/empty/Core/Src/stm32f7xx_it.c)
  * the [system initialization code](./templates/empty/Core/Src/system_stm32f7xx.c), called just before `main`, to setup the memory (external RAM, FLASH...), relocate interrupt vector table, setting clocks
  * the [application entry point](./templates/empty/Core/Src/main.c), the error handler, and `asset_failed` definition

LD1 -> SB8 -> ARD_D13 -> PI1
SW1 -> SB6 -> B_USER -> PI11

## LVGL

The LVGL portage need display and input drivers.

  1. [`tft.c`](./templates/lvgl/Core/Src/tft.c) is the for the display, it declares the display buffer `static lv_disp_buf_t disp_buf_1;`, which is initialized right after. The rendering function is `static void ex_disp_flush(lv_disp_drv_t*, const lv_area_t*, lv_color_t*)`, it is registered as a callback by `disp_drv.flush_cb = ex_disp_flush;`
  2. [`touchpad.c`](./templates/lvgl/Core/Src/touchpad.c) for the capacitive touchscreed input. It only contains a function to read the input, there `bool touchpad_read(lv_indev_drv_t*, lv_indev_data_t*)`, registered as callback with `indev_drv.read_cb = touchpad_read;`

Then, to run the GUI, two functions must be periodically called:
  1. [`lv_tick_inc`](./templates/lvgl/Core/Src/stm32f7xx_hal_msp.c) to increment the LVGL internal tick counter in ms. Must be called with the nb of ms ellapsed since its last call.
  2. [`lv_task_handler`](./templates/lvgl/Core/Src/main.c) to grab pending inputs if any, and updates the GUI.

TODO: LV_LVGL_H_INCLUDE_SIMPLE

---

## TODOs

  * Keep CubeMX comments and layout in main.c, stm32f7xx_hal_msp.c and others
  * `printf` plugged to SWO
  * debug configurations for other servers, without SWO, GUI, detailing SWO, copy necessary dbg ressources into new project.
  * Handling 3rd part libraries: FreeRTOS and LVGL with git submodules
  * Makefile documentation.
  * harmonizing `STM32CubeIDE` and `make` compile flags.
  * How to automate [Cube repo](https://github.com/STMicroelectronics/STM32CubeF7) installation.
  * `STM32CubeMx` config.

---

## Credits

Released by [JFA](jf.argentino@peugeotp4.fr) for ENGENEO under License Apache V2

Originates from this [jaz303 repo](https://github.com/jaz303/stm32f746g-discovery-gcc.git).

Probably some inspirations from this [mofosyne repo](https://github.com/mofosyne/stm32h7xx-cubemx-makefile-openocd-gdbgui-example.git) too.
