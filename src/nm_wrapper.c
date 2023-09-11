#include <ft_nm.h>

void handle_elf32(char *file_name, uint8_t *map, off_t file_size) {
  (void)file_name;
  (void)file_size;
  (void)map;
  ft_printf_fd(2, "32 bits not handle yet...\n");
}

int set_elf64_infos(t_elf64 *elf, uint8_t *map, char *file_name,
                    off_t file_size) {
  elf->map = map;
  elf->file_name = file_name;
  elf->file_size = file_size;
  elf->header = (Elf64_Ehdr *)map;
  elf->sections = (Elf64_Shdr *)&map[elf->header->e_shoff];
  elf->shstrtab =
      (char *)&map[elf->sections[elf->header->e_shstrndx].sh_offset];

  for (int i = 0; i < elf->header->e_shnum; i++) {
    const char *section_name = &elf->shstrtab[elf->sections[i].sh_name];

    if (!ft_strncmp(".symtab", section_name, ft_strlen(".symtab")) &&
        elf->sections[i].sh_type == SHT_SYMTAB) {
      elf->symtab = (Elf64_Sym *)&map[elf->sections[i].sh_offset];
      elf->symtab_size = elf->sections[i].sh_size;
    }
    if (!ft_strncmp(".strtab", section_name, ft_strlen(".strtab")) &&
        elf->sections[i].sh_type == SHT_STRTAB) {
      elf->strtab = (char *)&map[elf->sections[i].sh_offset];
    }
    if (!ft_strncmp(".dynsym", section_name, ft_strlen(".dynsym")) &&
        elf->sections[i].sh_type == SHT_DYNSYM) {
      elf->dynsym = (Elf64_Sym *)&map[elf->sections[i].sh_offset];
      elf->dynsym_size = elf->sections[i].sh_size;
    }
    if (!ft_strncmp(".dynstr", section_name, ft_strlen(".dynstr")) &&
        elf->sections[i].sh_type == SHT_STRTAB) {
      elf->dynstr = (char *)&map[elf->sections[i].sh_offset];
    }
  }
  return EXIT_SUCCESS;
}

void print_symtab(t_elf64 elf) {
  ft_printf("symtab: \n");
  for (uint64_t i = 0; i < elf.symtab_size / sizeof(Elf64_Sym); i++) {
    char *sym_name = &elf.strtab[elf.symtab[i].st_name];
    ft_printf("[%d] %s", i, sym_name);
    ft_printf(" %p\n", elf.symtab[i].st_value);
  }
}

void print_dynsym(t_elf64 elf) {
  ft_printf("dynsym: \n");
  for (uint64_t i = 0; i < elf.dynsym_size / sizeof(Elf64_Sym); i++) {
    char *sym_name = &elf.dynstr[elf.dynsym[i].st_name];
    ft_printf("[%d] %s ", i, sym_name);
    if (elf.dynsym[i].st_value)
      ft_printf("%p", elf.dynsym[i].st_value);
    ft_printf("\n");
  }
}

void handle_elf64(char *file_name, uint8_t *map, off_t file_size) {
  (void)file_name;
  t_elf64 elf = {0};

  set_elf64_infos(&elf, map, file_name, file_size);
  print_symtab(elf);
  print_dynsym(elf);
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
