#include <ft_nm.h>

void handle_elf32(char *file_name, uint8_t *map, off_t file_size) {
  (void)file_name;
  (void)file_size;
  (void)map;
  ft_printf_fd(2, "32 bits not handle yet...\n");
}
void handle_elf64(char *file_name, uint8_t *map, off_t file_size) {
  (void)file_name;
  (void)file_size;
  Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
  Elf64_Shdr *shdr = (Elf64_Shdr *)(map + (ehdr->e_shoff));
  char *shstrtab = (char *)&map[shdr[ehdr->e_shstrndx].sh_offset];
  Elf64_Sym *symtab = NULL;
  Elf64_Dyn *dynsym = NULL;
  uint64_t symtab_size = 0, dynsym_size = 0;
  char *dynstr = NULL, *strtab = NULL;
  (void)dynsym;
  (void)dynstr;
  (void)dynsym_size;

  for (int i = 0; i < ehdr->e_shnum; i++) {
    const char *section_name = &shstrtab[shdr[i].sh_name];

    if (!ft_strncmp(".symtab", section_name, ft_strlen(".symtab")) &&
        shdr[i].sh_type == SHT_SYMTAB) {
      symtab = (Elf64_Sym *)&shdr[i];
      symtab_size = shdr[i].sh_size;
    }
    if (!ft_strncmp(".strtab", section_name, ft_strlen(".strtab")) &&
        shdr[i].sh_type == SHT_STRTAB) {
      strtab = (char *)&map[shdr[i].sh_offset];
    }
    if (!ft_strncmp(section_name, ".dynsym", ft_strlen(".dynsym")) &&
        shdr[i].sh_type == SHT_DYNSYM) {
      dynsym = (Elf64_Dyn *)&shdr[i];
      dynsym_size = shdr[i].sh_size;
    }
    if (!ft_strncmp(".dynstr", section_name, ft_strlen(".dynstr")) &&
        shdr[i].sh_type == SHT_STRTAB) {
      dynstr = (char *)&map[shdr[i].sh_offset];
    }
  }

  for (uint64_t i = 0; i < symtab_size / sizeof(Elf64_Sym); i++) {
    char *sym_name = &strtab[symtab[i].st_name];
    if (*sym_name == '\x00')
      ft_printf("[%d] NULL", i);
    else
      ft_printf("[%d] %s", i, sym_name);
    ft_printf(" %p\n", symtab[i].st_value);
  }
}

int nm_wrapper(char *file_name) {
  uint8_t *map = NULL;
  off_t file_size = 0;
  char arch = 0;

  if (init(file_name, &map, &file_size, &arch))
    return EXIT_FAILURE;
  if (arch == ELFCLASS32)
    handle_elf32(file_name, map, file_size);
  else
    handle_elf64(file_name, map, file_size);
  munmap(map, file_size);
  return EXIT_SUCCESS;
}
