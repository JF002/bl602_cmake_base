# Build your own RISC-V toolchain on a ARM computer (PinebookPro)
In this article, I'll you how I build my own RISC-V toolchain on the [PinebookPro from Pine64](https://www.pine64.org/pinebook-pro/).

The whole process is not that hard but it takes a bit of time...

## Checkout the sources and build
**wARNING** : The source code, the build directory and the binaries use a lot of hard drive space. After the build, my source folder was 14GB big, and built binaries use 1.2GB. Make sure you have enough free space on you hard drive! In this case, I use a NVME SSD installed in my PinebookPro.

First, clone the source code...

```
git clone https://github.com/riscv/riscv-gnu-toolchain
```

... and initialize the submodules:

```
cd riscv-gnu-toolchain
git submodule update --init --recursive
```

Then configure the project:

```
./configure --prefix=<output directory> --enable-multilib
```

Of course, replace **<output directory>** by the destination folder for your toolchain. For example : `/opt/riscv`.

Multilib is needed to enable support for both **riscv64** and **riscv32** arthictectures.

Finally, build the toolchain:

```
make -j 4
```

This will take quite some time (I didn't measure it, but I would say somewhere between 2 and 3 hours).
