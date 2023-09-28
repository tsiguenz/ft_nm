#include <ft_nm.h>

static int push_symbol(t_symbol32 **lst, char *name, Elf32_Addr value,
                       char type) {
  t_symbol32 *tmp = *lst;
  t_symbol32 *new = malloc(1 * sizeof(t_symbol32));

  if (!new)
    return EXIT_FAILURE;
  new->name  = name;
  new->value = value;
  new->type  = type;
  new->next  = NULL;
  new->prev  = NULL;
  if (!*lst) {
    *lst = new;
    return EXIT_SUCCESS;
  }
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  new->prev = tmp;
  return EXIT_SUCCESS;
}

// Symbol to be deleted is a
static int is_duplicate_symbol(t_symbol32 *a, t_symbol32 *b) {
  // This is a symbol not printed by nm but idk why
  const char *useless_symbol_name = "program_invocation_short_name";
  int         is_useless_symbol =
      !ft_strncmp(useless_symbol_name, a->name, ft_strlen(useless_symbol_name));
  int a_len        = ft_strlen(a->name);
  int a_equal_to_b = ft_strlen(a->name) && !ft_strncmp(a->name, b->name, a_len);
  int b_char_is_end_or_arobase =
      (a->name[a_len] == '\0' &&
       (b->name[a_len] == '\0' || b->name[a_len] == '@'));
  int value_is_same = a->value == b->value;
  int is_debug      = a->type == b->type && a->type == 'a';

  return is_useless_symbol || (a_equal_to_b && b_char_is_end_or_arobase &&
                               value_is_same && !is_debug);
}

static int get_infos_and_push_symbol(char *name, const Elf32_Addr value,
                                     Elf32_Sym sym, t_elf32 elf,
                                     t_symbol32 **lst) {
  char type;
  int  is_empty = *name == '\0' && value <= 0;
  char st_type  = ELF32_ST_TYPE(sym.st_info);
  if (set_type32(&type, sym, elf))
    return EXIT_FAILURE;
  if (is_empty && st_type == STT_SECTION) {
    Elf32_Shdr section = {0};
    set_section_by_index32(&section, sym.st_shndx, elf);
    if (section.sh_name != 0)
      name = &elf.shstrtab[section.sh_name];
    is_empty = *name == '\0' && value <= 0;
    if (type == 'n')
      type = 'N';
  }
  if (is_empty && type != 'a')
    return EXIT_SUCCESS;
  if (push_symbol(lst, name, value, type))
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

static int parse_symtab(t_elf32 elf, t_symbol32 **lst) {
  Elf32_Sym *symtab = elf.symtab;
  for (uint32_t i = 1; i < elf.symtab_size / sizeof(Elf32_Sym); i++) {
    const uint32_t   name_index = symtab[i].st_name;
    const Elf32_Addr value      = symtab[i].st_value;
    char            *name;

    if (elf.strtab + name_index > (char *) (elf.map + elf.file_size)) {
      clear_list32(lst);
      return EXIT_FAILURE;
    }
    name = elf.strtab + name_index;
    if (get_infos_and_push_symbol(name, value, symtab[i], elf, lst)) {
      clear_list32(lst);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

static int parse_dynsym(t_elf32 elf, t_symbol32 **lst) {
  Elf32_Sym *dynsym = elf.dynsym;
  for (uint32_t i = 1; i < elf.dynsym_size / sizeof(Elf32_Sym); i++) {
    const uint32_t   name_index = dynsym[i].st_name;
    const Elf32_Addr value      = dynsym[i].st_value;
    char            *name;

    if (elf.dynstr + name_index > (char *) (elf.map + elf.file_size)) {
      clear_list32(lst);
      return EXIT_FAILURE;
    }
    name = elf.dynstr + name_index;
    if (get_infos_and_push_symbol(name, value, dynsym[i], elf, lst)) {
      clear_list32(lst);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int set_elf32_infos(t_elf32 *elf, uint8_t *map, char *file_name,
                    off_t file_size) {
  elf->map                   = map;
  elf->file_name             = file_name;
  elf->file_size             = file_size;
  elf->header                = (Elf32_Ehdr *) map;
  const uint32_t sh_offset   = elf->header->e_shoff;
  const uint16_t shstr_index = elf->header->e_shstrndx;
  const uint16_t nb_sections = elf->header->e_shnum;
  uint32_t       shstr_offset;

  if (sh_offset > (uint32_t) file_size || !sh_offset ||
      shstr_index > nb_sections)
    return EXIT_FAILURE;
  elf->sections = (Elf32_Shdr *) (map + sh_offset);
  shstr_offset  = elf->sections[shstr_index].sh_offset;
  if (shstr_offset > (uint32_t) file_size)
    return EXIT_FAILURE;
  elf->shstrtab = (char *) map + shstr_offset;

  for (int i = 0; i < nb_sections; i++) {
    const Elf32_Shdr current_section    = elf->sections[i];
    const uint32_t   section_size       = current_section.sh_size;
    const uint32_t   section_name_index = current_section.sh_name;
    const uint32_t   section_offset     = current_section.sh_offset;
    const char      *section_name       = elf->shstrtab + section_name_index;
    const uint32_t   section_type       = current_section.sh_type;

    if ((section_type != SHT_NOBITS &&
         section_size + section_offset > (uint32_t) file_size) ||
        section_name_index > (uint32_t) file_size) {
      return EXIT_FAILURE;
    }

    if (!ft_strncmp(".symtab", section_name, ft_strlen(".symtab")) &&
        section_type == SHT_SYMTAB) {
      elf->symtab      = (Elf32_Sym *) (map + section_offset);
      elf->symtab_size = section_size;
    }
    if (!ft_strncmp(".strtab", section_name, ft_strlen(".strtab")) &&
        section_type == SHT_STRTAB) {
      elf->strtab = (char *) (map + section_offset);
    }
    if (!ft_strncmp(".dynsym", section_name, ft_strlen(".dynsym")) &&
        section_type == SHT_DYNSYM) {
      elf->dynsym      = (Elf32_Sym *) (map + section_offset);
      elf->dynsym_size = section_size;
    }
    if (!ft_strncmp(".dynstr", section_name, ft_strlen(".dynstr")) &&
        section_type == SHT_STRTAB) {
      elf->dynstr = (char *) (map + section_offset);
    }
  }
  if (!elf->symtab) {
    // in case of bad offset but not stripped
    if (elf->symtab != (Elf32_Sym *) map)
      return EXIT_FAILURE;
    if (nb_files > 1)
      ft_printf("\n%s:\n", file_name);
    ft_printf_fd(2, "%s: %s: no symbols\n", prog_name, file_name);
    file_is_stripped = 1;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void clear_list32(t_symbol32 **lst) {
  if (!lst || !*lst)
    return;
  t_symbol32 *tmp;

  while (lst && *lst) {
    tmp = (*lst)->next;
    free(*lst);
    *lst = tmp;
  }
  *lst = NULL;
}

void delete_duplicates_symbols32(t_symbol32 **lst) {
  t_symbol32 *current = *lst;
  t_symbol32 *tmp;

  while (current) {
    tmp = *lst;
    while (tmp) {
      t_symbol32 *next = tmp->next;
      if (current != tmp && is_duplicate_symbol(tmp, current) &&
          !is_debug_symbol32(tmp->type, tmp->name)) {
        if (tmp == *lst) {
          *lst         = tmp->next;
          (*lst)->prev = NULL;
        } else {
          tmp->prev->next = tmp->next;
          if (tmp->next)
            tmp->next->prev = tmp->prev;
        }
        free(tmp);
      }
      tmp = next;
    }
    current = current->next;
  }
}

int parse_symbols32(t_elf32 elf, t_symbol32 **lst) {
  if (parse_symtab(elf, lst) || parse_dynsym(elf, lst)) {
    clear_list32(lst);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
