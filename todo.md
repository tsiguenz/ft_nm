# TODO

Segfault sometimes:

```
./ft_nm test/bin/bad_files/32_changed_to_64_bits test/bin/bad_files/42 test/bin/bad_files/64_changed_to_32_bits test/bin/bad_files/bad_elf_class test/bin/bad_files/elf_changed_to_ela test/bin/bad_files/elfclassnone test/bin/bad_files/empty
```

## Test cases

### Functional tests

- [x] Multi files as argument

#### File format

- [x] ELF
- [x] directory
- [x] casual file
- [x] empty file

#### Architecture

- [x] x32
- [x] x64 (/lib)
- [x] byte equal to ELFCLASSNONE (use xxd to edit binary file)
- [x] x32 elf with arch byte change to x64
- [x] x64 elf with arch byte change to x32

### Permissions

- [x] No read permissions

### Bonuses

- [x] a
- [x] g
- [x] u
- [x] r
- [x] p
- [x] multiple
