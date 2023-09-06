# FT_NM

## Introduction

The aim of the project is to recode
[nm](https://man7.org/linux/man-pages/man1/nm.1.html) without options.
The bonuses are to recode -a -g -u -r -p.

## Create x86_32 binaries

- To create x86_32 binary use -m32 flag with gcc

## Edit binary file

1. Open file in vim in binary mode: `vim -b [filename]`

2. Use xxd to convert file to hexa in vim (bin to hex): `:%!xdd`

3. Edit your file! (be careful of the endianness of your CPU)

4. Then revert (hex to bin): `:%!xdd -r`

## Useful links

- [elf wiki](<https://en.wikipedia.org/wiki/Executable_and_Linkable_Format>)
- [man elf](https://www.man7.org/linux/man-pages/man5/elf.5.html)
- [binary dissection course](https://github.com/compilepeace/BINARY_DISSECTION_COURSE/tree/master)
