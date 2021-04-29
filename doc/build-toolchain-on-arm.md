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

Once the build is finished, the toolchain will be available in your **output directory**, and the compiler will be in the `bin/` folder:

```
$ ls -l
total 458564
-rwxr-xr-x 1 jf jf   5827288 Apr 29 08:41 riscv64-unknown-elf-addr2line
-rwxr-xr-x 2 jf jf   6025480 Apr 29 08:41 riscv64-unknown-elf-ar
-rwxr-xr-x 2 jf jf   7936856 Apr 29 08:41 riscv64-unknown-elf-as
-rwxr-xr-x 2 jf jf   7171240 Apr 29 10:48 riscv64-unknown-elf-c++
-rwxr-xr-x 1 jf jf   5780856 Apr 29 08:41 riscv64-unknown-elf-c++filt
-rwxr-xr-x 1 jf jf   7159408 Apr 29 10:48 riscv64-unknown-elf-cpp
-rwxr-xr-x 1 jf jf    139416 Apr 29 08:41 riscv64-unknown-elf-elfedit
-rwxr-xr-x 2 jf jf   7171240 Apr 29 10:48 riscv64-unknown-elf-g++
-rwxr-xr-x 2 jf jf   7147784 Apr 29 10:48 riscv64-unknown-elf-gcc
-rwxr-xr-x 2 jf jf   7147784 Apr 29 10:48 riscv64-unknown-elf-gcc-10.2.0
-rwxr-xr-x 1 jf jf    165376 Apr 29 10:48 riscv64-unknown-elf-gcc-ar
-rwxr-xr-x 1 jf jf    165256 Apr 29 10:48 riscv64-unknown-elf-gcc-nm
-rwxr-xr-x 1 jf jf    165264 Apr 29 10:48 riscv64-unknown-elf-gcc-ranlib
-rwxr-xr-x 1 jf jf   5192608 Apr 29 10:48 riscv64-unknown-elf-gcov
-rwxr-xr-x 1 jf jf   3584712 Apr 29 10:48 riscv64-unknown-elf-gcov-dump
-rwxr-xr-x 1 jf jf   3739016 Apr 29 10:48 riscv64-unknown-elf-gcov-tool
-rwxr-xr-x 1 jf jf 119081544 Apr 29 09:11 riscv64-unknown-elf-gdb
-rwxr-xr-x 1 jf jf      4045 Apr 29 09:11 riscv64-unknown-elf-gdb-add-index
-rwxr-xr-x 1 jf jf   6390960 Apr 29 08:41 riscv64-unknown-elf-gprof
-rwxr-xr-x 4 jf jf   9413072 Apr 29 08:41 riscv64-unknown-elf-ld
-rwxr-xr-x 4 jf jf   9413072 Apr 29 08:41 riscv64-unknown-elf-ld.bfd
-rwxr-xr-x 1 jf jf 190508352 Apr 29 10:48 riscv64-unknown-elf-lto-dump
-rwxr-xr-x 2 jf jf   5879296 Apr 29 08:41 riscv64-unknown-elf-nm
-rwxr-xr-x 2 jf jf   6761240 Apr 29 08:41 riscv64-unknown-elf-objcopy
-rwxr-xr-x 2 jf jf   9633136 Apr 29 08:41 riscv64-unknown-elf-objdump
-rwxr-xr-x 2 jf jf   6025488 Apr 29 08:41 riscv64-unknown-elf-ranlib
-rwxr-xr-x 2 jf jf   4687152 Apr 29 08:41 riscv64-unknown-elf-readelf
-rwxr-xr-x 1 jf jf   8771656 Apr 29 09:10 riscv64-unknown-elf-run
-rwxr-xr-x 1 jf jf   5830808 Apr 29 08:41 riscv64-unknown-elf-size
-rwxr-xr-x 1 jf jf   5820808 Apr 29 08:41 riscv64-unknown-elf-strings
-rwxr-xr-x 2 jf jf   6761240 Apr 29 08:41 riscv64-unknown-elf-strip
```

## Using the toolchain

You can now use the cmake command line to build this project using your toolchain :

```
cmake -DRISCV_TOOLCHAIN_BIN_PATH=<output directory>/bin ..
```