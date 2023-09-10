# TODO

- **DO UNIT TESTS AND CI BEFORE THE PROJECT WAS FINISHED PLS**
- Use perror instead of my errors

## Test cases

### Functional tests

- [ ] Multi files as argument

#### File format

- [ ] ELF
- [ ] directory
- [ ] casual file
- [ ] empty file

#### Architecture

- [ ] x32 (/lib32)
- [ ] x64 (/lib)
- [ ] byte equal to ELFCLASSNONE (use xxd to edit binary file)
- [ ] x32 elf with arch byte change to x64
- [ ] x64 elf with arch byte change to x32
- [ ] file with offset point out of the mapped content

### Permissions

- [ ] No read permissions
