#include <ft_nm.h>

int set_elf64_infos(t_elf64 *elf, uint8_t *map, char *file_name,
                    off_t file_size) {
  elf->map       = map;
  elf->file_name = file_name;
  elf->file_size = file_size;
  elf->header    = (Elf64_Ehdr *) map;
  elf->sections  = (Elf64_Shdr *) &map[elf->header->e_shoff];
  elf->shstrtab =
      (char *) &map[elf->sections[elf->header->e_shstrndx].sh_offset];

  for (int i = 0; i < elf->header->e_shnum; i++) {
    const char *section_name = &elf->shstrtab[elf->sections[i].sh_name];

    if (!ft_strncmp(".symtab", section_name, ft_strlen(".symtab")) &&
        elf->sections[i].sh_type == SHT_SYMTAB) {
      elf->symtab      = (Elf64_Sym *) &map[elf->sections[i].sh_offset];
      elf->symtab_size = elf->sections[i].sh_size;
    }
    if (!ft_strncmp(".strtab", section_name, ft_strlen(".strtab")) &&
        elf->sections[i].sh_type == SHT_STRTAB) {
      elf->strtab = (char *) &map[elf->sections[i].sh_offset];
    }
    if (!ft_strncmp(".dynsym", section_name, ft_strlen(".dynsym")) &&
        elf->sections[i].sh_type == SHT_DYNSYM) {
      elf->dynsym      = (Elf64_Sym *) &map[elf->sections[i].sh_offset];
      elf->dynsym_size = elf->sections[i].sh_size;
    }
    if (!ft_strncmp(".dynstr", section_name, ft_strlen(".dynstr")) &&
        elf->sections[i].sh_type == SHT_STRTAB) {
      elf->dynstr = (char *) &map[elf->sections[i].sh_offset];
    }
  }
  return EXIT_SUCCESS;
}

int push_symbol(t_symbol **lst, char *name, Elf64_Addr value, char type) {
  t_symbol *tmp = *lst;
  t_symbol *new = malloc(1 * sizeof(t_symbol));

  if (!new)
    return EXIT_FAILURE;
  new->name  = name;
  new->value = value;
  new->type  = type;
  new->next  = NULL;
  if (!*lst) {
    *lst = new;
    return EXIT_SUCCESS;
  }
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  return EXIT_SUCCESS;
}

void clear_list(t_symbol **lst) {
  if (!lst || !*lst)
    return;
  t_symbol *tmp;

  while (lst && *lst) {
    tmp = (*lst)->next;
    free(*lst);
    *lst = tmp;
  }
  *lst = NULL;
}

int get_section_by_index64(Elf64_Shdr *section, int index, t_elf64 elf) {
  if (index < 1 || index >= elf.header->e_shnum)
    return EXIT_FAILURE;
  *section = elf.sections[index];
  return EXIT_SUCCESS;
}

static int is_data_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".data";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_text_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".text";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_fini_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".fini";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_fini_array_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".fini_array";
  return section.sh_type == SHT_FINI_ARRAY &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_init_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".init";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_init_array_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".init_array";
  return section.sh_type == SHT_INIT_ARRAY &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_bss_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".bss";
  return section.sh_type == SHT_NOBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_dynamic_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".dynamic";
  return section.sh_type == SHT_DYNAMIC &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

static int is_got_section(Elf64_Shdr section, t_elf64 elf) {
  const char *section_name = ".got";
  return section.sh_type == SHT_PROGBITS &&
         !ft_strncmp(section_name, &elf.shstrtab[section.sh_name],
                     ft_strlen(section_name));
}

int is_readonly_section(Elf64_Shdr section) {
  return section.sh_flags != SHF_WRITE;
}

static int set_type(char *type, Elf64_Sym symbol, t_elf64 elf,
                    char *symbol_name) {
  (void) symbol_name;
  char       st_bind = ELF64_ST_BIND(symbol.st_info);
  char       st_type = ELF64_ST_TYPE(symbol.st_info);
  char       shndx   = symbol.st_shndx;
  Elf64_Shdr section = {0};

  // ft_printf("%s type: %d shndx: %d st_bind: %d\n",  //
  // symbol_name, st_type, shndx, st_bind);
  *type = '?';
  if (is_readonly_section(section))
    *type = 'r';
  if (get_section_by_index64(&section, shndx, elf))
    *type = 'u';
  if (is_text_section(section, elf) || is_init_section(section, elf) ||
      is_fini_section(section, elf))
    *type = 't';
  if (is_data_section(section, elf) || is_fini_array_section(section, elf) ||
      is_init_array_section(section, elf) || is_got_section(section, elf) ||
      is_dynamic_section(section, elf))
    *type = 'd';
  if (is_bss_section(section, elf))
    *type = 'b';
  if (st_type == STT_FILE)
    *type = 'a';
  if (st_bind == STB_WEAK)
    *type = 'w';
  if (st_bind == STB_GLOBAL && *type != '?')
    *type -= 32;
  return EXIT_SUCCESS;
}

void delete_duplicates_symbols(t_symbol **lst) {
  t_symbol *tmp = *lst;

  // delete tmp instead of next
  while (tmp && tmp->next) {
    t_symbol *next = tmp->next;
    if (!ft_strlen(tmp->name)) {
      tmp = tmp->next;
      continue;
    }
    if (!ft_strncmp(tmp->name, next->name, ft_strlen(tmp->name))) {
      tmp->next = next->next;
      free(next);
    }
    tmp = tmp->next;
  }
}

static int parse_symtab(t_elf64 elf, t_symbol **lst) {
  Elf64_Sym *symtab = elf.symtab;
  for (uint64_t i = 1; i < elf.symtab_size / sizeof(Elf64_Sym); i++) {
    char      *name  = &elf.strtab[symtab[i].st_name];
    Elf64_Addr value = symtab[i].st_value;
    char       type;

    if (set_type(&type, symtab[i], elf, name) ||
        push_symbol(lst, name, value, type)) {
      clear_list(lst);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

static int parse_dynsym(t_elf64 elf, t_symbol **lst) {
  Elf64_Sym *dynsym = elf.dynsym;
  for (uint64_t i = 1; i < elf.dynsym_size / sizeof(Elf64_Sym); i++) {
    char      *name  = &elf.dynstr[dynsym[i].st_name];
    Elf64_Addr value = dynsym[i].st_value;
    char       type;

    if (*name == '\0' && value == 0)
      continue;
    if (set_type(&type, dynsym[i], elf, name) ||
        push_symbol(lst, name, value, type)) {
      clear_list(lst);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int parse_symbols64(t_elf64 elf, t_symbol **lst) {
  if (parse_symtab(elf, lst) || parse_dynsym(elf, lst)) {
    clear_list(lst);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
