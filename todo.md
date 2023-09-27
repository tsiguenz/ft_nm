# TODO

## Test cases

### Functional tests

- [x] Multi files as argument

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

### Permissions

- [x] No read permissions

### Bonuses

- [x] a
- [x] g
- [x] u
- [x] r
- [x] p
- [ ] multiple

### Misc

- [ ] file with offset point out of the mapped content
- [ ] change the value of sh_link
