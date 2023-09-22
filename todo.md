# TODO

- handle multipe files
- handle arguments for bonuses
- test bonuses
- do -h for bad argument ?

```
Usage: ft_nm [option(s)] [file(s)]
    List symbols in [file(s)] (a.out by default).
    The options are:
    -a: Display debugger-only symbols
    -g: Display only external symbols
    -u: Display only undefined symbols
    -r: Reverse the sense of the sort
    -p: Do not sort the symbols
ft_nm: supported targets: 86_32, x64, object files, .so
```

## Test cases

### Functional tests

- [ ] Multi files as argument

#### File format

- [x] ELF
- [x] directory
- [x] casual file
- [x] empty file

#### Architecture

- [ ] x32 (/lib32)
- [x] x64 (/lib)
- [x] byte equal to ELFCLASSNONE (use xxd to edit binary file)
- [x] x32 elf with arch byte change to x64
- [ ] x64 elf with arch byte change to x32

### Misc

- [ ] file with offset point out of the mapped content
- [ ] change the value of sh_link

### Permissions

- [x] No read permissions
