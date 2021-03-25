# bl602_cmake_base
CMake project for BL602 RISC-V processor

# How to build
*NOTE :* This project uses a pre-compiled version of the [Buffalo SDK (bl_iot_sdk)](https://github.com/bouffalolab/bl_iot_sdk) located in the folder **sdk**.

Create a build directory and run CMake:

```
mkdir build
cd build
cmake -DRISCV_TOOLCHAIN_BIN_PATH=<path_to_the_riscv_toolchain> ..
make
```

The files `BL602_Cmake.bin`, `BL602_Cmake.out` and `BL602_Cmake.hex` are generated.

You can use a [flasher for the BL602](https://github.com/mkroman/awesome-bouffalo#rom-tools) to flash the firmware to the BL602 using the USB-To-Serial port. 