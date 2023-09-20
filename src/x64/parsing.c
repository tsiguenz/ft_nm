#include <ft_nm.h>

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

static int is_duplicate_symbol(t_symbol *tmp, t_symbol *next) {
  int tmp_len = ft_strlen(tmp->name);
  int tmp_equal_to_next =
      ft_strlen(tmp->name) && !ft_strncmp(tmp->name, next->name, tmp_len);
  int next_char_is_end_or_arobase =
      (tmp->name[tmp_len] == '\0' &&
       (next->name[tmp_len] == '\0' || next->name[tmp_len] == '@'));
  int value_is_same = tmp->value == next->value;

  return tmp_equal_to_next && next_char_is_end_or_arobase && value_is_same;
}

static int parse_symtab(t_elf64 elf, t_symbol **lst) {
  Elf64_Sym *symtab = elf.symtab;
  for (uint64_t i = 1; i < elf.symtab_size / sizeof(Elf64_Sym); i++) {
    uint32_t   name_index = symtab[i].st_name;
    char      *name       = &elf.strtab[name_index];
    Elf64_Addr value      = symtab[i].st_value;
    char       type;

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
    char      *name  = &elf.dynstr[dynsym[i].st_name];
    Elf64_Addr value = dynsym[i].st_value;
    char       type;

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

  if (section_offset > (uint64_t) file_size || shstr_index < nb_sections)
    return EXIT_FAILURE;
  const uint32_t shstr_offset = elf->sections[shstr_index].sh_offset;
  if (shstr_offset > (uint32_t) file_size)
    return EXIT_FAILURE;
  elf->sections = (Elf64_Shdr *) &map[section_offset];
  elf->shstrtab = (char *) &map[shstr_offset];

  for (int i = 0; i < nb_sections; i++) {
    const Elf64_Shdr current_section    = elf->sections[i];
    const uint64_t   section_size       = current_section.sh_size;
    const uint32_t   section_name_index = current_section.sh_name;
    const uint32_t   section_offset     = current_section.sh_offset;
    const char      *section_name       = &elf->shstrtab[section_name_index];

    if (section_size > (uint64_t) file_size ||
        section_name_index > (uint32_t) file_size ||
        section_offset > (uint32_t) file_size)
      return EXIT_FAILURE;

    if (!ft_strncmp(".symtab", section_name, ft_strlen(".symtab")) &&
        elf->sections[i].sh_type == SHT_SYMTAB) {
      elf->symtab      = (Elf64_Sym *) &map[section_offset];
      elf->symtab_size = section_size;
    }
    if (!ft_strncmp(".strtab", section_name, ft_strlen(".strtab")) &&
        elf->sections[i].sh_type == SHT_STRTAB) {
      elf->strtab = (char *) &map[section_offset];
    }
    if (!ft_strncmp(".dynsym", section_name, ft_strlen(".dynsym")) &&
        elf->sections[i].sh_type == SHT_DYNSYM) {
      elf->dynsym      = (Elf64_Sym *) &map[section_offset];
      elf->dynsym_size = section_size;
    }
    if (!ft_strncmp(".dynstr", section_name, ft_strlen(".dynstr")) &&
        elf->sections[i].sh_type == SHT_STRTAB) {
      elf->dynstr = (char *) &map[section_offset];
    }
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
  t_symbol *tmp = *lst;

  while (tmp && tmp->next) {
    t_symbol *next = tmp->next;
    if (is_duplicate_symbol(tmp, next)) {
      if (tmp == *lst)
        *lst = next;
      else
        tmp->prev->next = next;
      next->prev = tmp->prev;
      free(tmp);
    }
    tmp = next;
  }
}

int parse_symbols64(t_elf64 elf, t_symbol **lst) {
  if (parse_symtab(elf, lst) || parse_dynsym(elf, lst)) {
    clear_list(lst);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
