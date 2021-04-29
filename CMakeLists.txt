cmake_minimum_required(VERSION 3.17)
project(BL602_Cmake)

include(cmake/riscv-gcc-toolchain.cmake)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 14)

set(BL_SDK_PATH "${CMAKE_SOURCE_DIR}/sdk")

set(COMMON_FLAGS "-march=rv32imafc -mabi=ilp32f -MMD")

set(CMAKE_C_FLAGS "-c -std=gnu99 -Os -gdwarf -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -fshort-enums -ffreestanding -fno-strict-aliasing ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "-c -Os -std=c++11 -gdwarf -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -fshort-enums -ffreestanding -fno-strict-aliasing -fno-use-cxa-atexit -nostdlib -Wpointer-arith -fexceptions -fstack-protector -fno-rtti -fno-exceptions -fms-extensions -Werror=return-type ${COMMON_FLAGS}")

set(CMAKE_ASM_FLAGS "-MP -MD -x assembler-with-cpp")

set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_COMPILER} <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_C_COMPILER} ${COMMON_FLAGS} <LINK_FLAGS> <OBJECTS> -lstdc++ -o <TARGET> <LINK_LIBRARIES>")

add_definitions(-DCONF_USER_ENABLE_PSRAM -DconfigUSE_TICKLESS_IDLE=0 -DFEATURE_WIFI_DISABLE=1 -DCFG_FREERTOS -DARCH_RISCV -DBL602 -DCONFIG_SET_TX_PWR -DCFG_BLE_ENABLE -DBFLB_BLE -DCFG_BLE -DCFG_SLEEP -DOPTIMIZE_DATA_EVT_FLOW_FROM_CONTROLLER -DCFG_CON=2 -DCFG_BLE_TX_BUFF_DATA=2 -DCONFIG_BT_ALLROLES -DCONFIG_BT_CENTRAL -DCONFIG_BT_OBSERVER -DCONFIG_BT_PERIPHERAL -DCONFIG_BT_BROADCASTER -DCONFIG_BT_L2CAP_DYNAMIC_CHANNEL -DCONFIG_BT_GATT_CLIENT -DCONFIG_BT_CONN -DCONFIG_BT_GATT_DIS_PNP -DCONFIG_BT_GATT_DIS_SERIAL_NUMBER -DCONFIG_BT_GATT_DIS_FW_REV -DCONFIG_BT_GATT_DIS_HW_REV -DCONFIG_BT_GATT_DIS_SW_REV -DCONFIG_BT_ECC -DCONFIG_BT_GATT_DYNAMIC_DB -DCONFIG_BT_GATT_SERVICE_CHANGED -DCONFIG_BT_KEYS_OVERWRITE_OLDEST -DCONFIG_BT_KEYS_SAVE_AGING_COUNTER_ON_P -DCONFIG_BT_GAP_PERIPHERAL_PREF_PARAMS -DCONFIG_BT_BONDABLE -DCONFIG_BT_HCI_VS_EVT_USER -DCONFIG_BT_ASSERT -DCONFIG_BT_SMP -DCONFIG_BT_SIGNING -DCONFIG_BT_SETTINGS_CCC_LAZY_LOADING -DCONFIG_BT_SETTINGS_USE_PRINTK -DCFG_BLE_STACK_DBG_PRINT -D BL_SDK_VER={sdk.version} -D BL_SDK_PHY_VER={sdk.phy_ver} -D BL_SDK_RF_VER={sdk.rf_ver} -D BL_CHIP_NAME=BL602 -DARCH_RISCV -DCONFIG_PSM_EASYFLASH_SIZE=16384 -DconfigUSE_TICKLESS_IDLE=0 -DFEATURE_WIFI_DISABLE=1 -DCFG_BLE_ENABLE -DCONF_USER_ENABLE_PSRAM -DCONF_USER_ENABLE_VFS_ROMFS -DCFG_COMPONENT_BLOG_ENABLE=0)

add_executable(BL602_Cmake main.cpp)

target_include_directories(BL602_Cmake PUBLIC
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram/config/
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram/portable/GCC/RISC-V/
        ${BL_SDK_PATH}/include/hal_drv/bl602_hal/
        ${BL_SDK_PATH}/include/sys/bltime/include/
        ${BL_SDK_PATH}/include/bl602/bl602
        ${BL_SDK_PATH}/include/bl602/bl602/include
        ${BL_SDK_PATH}/include/bl602/bl602_std
        ${BL_SDK_PATH}/include/bl602/bl602_std/include
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/StdDriver/Inc 
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Device/Bouffalo/BL602/Peripherals
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/RISCV/Device/Bouffalo/BL602/Startup
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/RISCV/Core/Include
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Include
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Common/platform_print
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Common/soft_crc
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Common/partition
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Common/xz
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Common/cipher_suite/inc
        ${BL_SDK_PATH}/include/bl602/bl602_std/bl602_std/Common/ring_buffer
        ${BL_SDK_PATH}/include/stage/blfdt
        ${BL_SDK_PATH}/include/stage/blfdt/include
        ${BL_SDK_PATH}/include/stage/blfdt/inc
        ${BL_SDK_PATH}/include/sys/blmtd
        ${BL_SDK_PATH}/include/sys/blmtd/include
        ${BL_SDK_PATH}/include/sys/blmtd/include
        ${BL_SDK_PATH}/include/stage/blog
        ${BL_SDK_PATH}/include/stage/blog/include
        ${BL_SDK_PATH}/include/stage/blog
        ${BL_SDK_PATH}/include/stage/blog_testc
        ${BL_SDK_PATH}/include/stage/blog_testc/include
        ${BL_SDK_PATH}/include/stage/blog_testc
        ${BL_SDK_PATH}/include/sys/bloop/bloop
        ${BL_SDK_PATH}/include/sys/bloop/bloop/include
        ${BL_SDK_PATH}/include/sys/bloop/bloop/include
        ${BL_SDK_PATH}/include/sys/bltime
        ${BL_SDK_PATH}/include/sys/bltime/include
        ${BL_SDK_PATH}/include/sys/bltime/include
        ${BL_SDK_PATH}/include/stage/cli
        ${BL_SDK_PATH}/include/stage/cli/include
        ${BL_SDK_PATH}/include/stage/cli/cli/include
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram/include
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram/config
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram/portable/GCC/RISC-V
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram/portable/GCC/RISC-V/chip_specific_extensions/RV32F_float_abi_single
        ${BL_SDK_PATH}/include/bl602/freertos_riscv_ram/panic
        ${BL_SDK_PATH}/include/hal_drv
        ${BL_SDK_PATH}/include/hal_drv/include
        ${BL_SDK_PATH}/include/hal_drv/bl602_hal
        ${BL_SDK_PATH}/include/sys/bloop/looprt
        ${BL_SDK_PATH}/include/sys/bloop/looprt/include
        ${BL_SDK_PATH}/include/sys/bloop/loopset
        ${BL_SDK_PATH}/include/sys/bloop/loopset/include
        ${BL_SDK_PATH}/include/fs/romfs
        ${BL_SDK_PATH}/include/fs/romfs/include
        ${BL_SDK_PATH}/include/utils
        ${BL_SDK_PATH}/include/utils/include
        ${BL_SDK_PATH}/include/fs/vfs
        ${BL_SDK_PATH}/include/fs/vfs/include
        ${BL_SDK_PATH}/include/fs/vfs/posix/include
        ${BL_SDK_PATH}/include/stage/yloop
        ${BL_SDK_PATH}/include/stage/yloop/include
)


target_link_directories(BL602_Cmake PUBLIC sdk/lib)

target_link_libraries(BL602_Cmake
        -Wl,--start-group
        bl602
        bl602_std
        blfdt
        blmtd
        blog
        blog_testc
        bloop
        bltime
        cli
        freertos_riscv_ram
        hal_drv
        looprt
        loopset
        romfs
        utils
        vfs
        yloop
        -Wl,--end-group -Wl,-EL -lm
        )

set_target_properties(BL602_Cmake PROPERTIES
        SUFFIX ".out"
        LINK_FLAGS "-T${BL_SDK_PATH}/ld/flash.ld -march=rv32imfc -mabi=ilp32f -Os -nostartfiles -Wl,--gc-sections -Wl,-static -Wl,--gc-sections"
        )


add_custom_command(TARGET BL602_Cmake
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} BL602_Cmake.out
        COMMAND ${CMAKE_OBJCOPY} -O binary BL602_Cmake.out "BL602_Cmake.bin"
        COMMAND ${CMAKE_OBJCOPY} -O ihex BL602_Cmake.out "BL602_Cmake.hex"
        COMMENT "post build steps for BL602_Cmake")
)
