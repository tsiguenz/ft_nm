#include <ft_nm.h>

int file_is_stripped = 0;

static int push_symbol(t_symbol **lst, char *name, Elf64_Addr value,
                       char type) {
  t_symbol *tmp = *lst;
  t_symbol *new = malloc(1 * sizeof(t_symbol));

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
static int is_duplicate_symbol(t_symbol *a, t_symbol *b) {
  const char *useless_symbol_name = "program_invocation_short_name";
  int         is_useless_symbol =
      !ft_strncmp(useless_symbol_name, a->name, ft_strlen(useless_symbol_name));
  int a_len        = ft_strlen(a->name);
  int a_equal_to_b = ft_strlen(a->name) && !ft_strncmp(a->name, b->name, a_len);
  int b_char_is_end_or_arobase =
      (a->name[a_len] == '\0' &&
       (b->name[a_len] == '\0' || b->name[a_len] == '@'));
  int value_is_same = a->value == b->value;

  return is_useless_symbol ||
         (a_equal_to_b && b_char_is_end_or_arobase && value_is_same);
}

static int parse_symtab(t_elf64 elf, t_symbol **lst) {
  Elf64_Sym *symtab = elf.symtab;
  for (uint64_t i = 1; i < elf.symtab_size / sizeof(Elf64_Sym); i++) {
    const uint32_t   name_index = symtab[i].st_name;
    const Elf64_Addr value      = symtab[i].st_value;
    char             type;
    char            *name;

    if (elf.strtab + name_index > (char *) (elf.map + elf.file_size)) {
      clear_list(lst);
      return EXIT_FAILURE;
    }
    name = elf.strtab + name_index;
    if (*name == '\0' && value <= 0)
      continue;
    if (set_type(&type, symtab[i], elf) ||
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
    const uint32_t   name_index = dynsym[i].st_name;
    const Elf64_Addr value      = dynsym[i].st_value;
    char             type;
    char            *name;

    if (elf.dynstr + name_index > (char *) (elf.map + elf.file_size)) {
      clear_list(lst);
      return EXIT_FAILURE;
    }
    name = elf.dynstr + name_index;
    if (*name == '\0' && value <= 0)
      continue;
    if (set_type(&type, dynsym[i], elf) ||
        push_symbol(lst, name, value, type)) {
      clear_list(lst);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int set_elf64_infos(t_elf64 *elf, uint8_t *map, char *file_name,
                    off_t file_size) {
  elf->map                      = map;
  elf->file_name                = file_name;
  elf->file_size                = file_size;
  elf->header                   = (Elf64_Ehdr *) map;
  const uint64_t section_offset = elf->header->e_shoff;
  const uint16_t shstr_index    = elf->header->e_shstrndx;
  const uint16_t nb_sections    = elf->header->e_shnum;

  if (section_offset > (uint64_t) file_size || !section_offset ||
      shstr_index > nb_sections)
    return EXIT_FAILURE;
  elf->sections               = (Elf64_Shdr *) (map + section_offset);
  const uint32_t shstr_offset = elf->sections[shstr_index].sh_offset;
  if (shstr_offset > (uint32_t) file_size)
    return EXIT_FAILURE;
  elf->shstrtab = (char *) map + shstr_offset;

  for (int i = 0; i < nb_sections; i++) {
    const Elf64_Shdr current_section    = elf->sections[i];
    const uint64_t   section_size       = current_section.sh_size;
    const uint32_t   section_name_index = current_section.sh_name;
    const uint32_t   section_offset     = current_section.sh_offset;
    const char      *section_name       = elf->shstrtab + section_name_index;
    const uint32_t   section_type       = current_section.sh_type;

    if ((section_type != SHT_NOBITS && section_size > (uint64_t) file_size) ||
        section_name_index > (uint32_t) file_size ||
        section_offset > (uint32_t) file_size) {
      return EXIT_FAILURE;
    }

    if (!ft_strncmp(".symtab", section_name, ft_strlen(".symtab")) &&
        section_type == SHT_SYMTAB) {
      elf->symtab      = (Elf64_Sym *) (map + section_offset);
      elf->symtab_size = section_size;
    }
    if (!ft_strncmp(".strtab", section_name, ft_strlen(".strtab")) &&
        section_type == SHT_STRTAB) {
      elf->strtab = (char *) (map + section_offset);
    }
    if (!ft_strncmp(".dynsym", section_name, ft_strlen(".dynsym")) &&
        section_type == SHT_DYNSYM) {
      elf->dynsym      = (Elf64_Sym *) (map + section_offset);
      elf->dynsym_size = section_size;
    }
    if (!ft_strncmp(".dynstr", section_name, ft_strlen(".dynstr")) &&
        section_type == SHT_STRTAB) {
      elf->dynstr = (char *) (map + section_offset);
    }
  }
  if (!elf->symtab) {
    ft_printf_fd(2, "%s: %s: no symbols\n", prog_name, file_name);
    file_is_stripped = 1;
    return EXIT_FAILURE;
  }
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

void delete_duplicates_symbols(t_symbol **lst) {
  t_symbol *current = *lst;
  t_symbol *tmp;

  while (current) {
    tmp = *lst;
    while (tmp) {
      t_symbol *next = tmp->next;
      if (current != tmp && is_duplicate_symbol(tmp, current)) {
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

int parse_symbols64(t_elf64 elf, t_symbol **lst) {
  if (parse_symtab(elf, lst) || parse_dynsym(elf, lst)) {
    clear_list(lst);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
