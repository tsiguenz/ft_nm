#include <ft_nm.h>

int handle_elf64(char *file_name, uint8_t *map, off_t file_size) {
  t_elf64   elf = {0};
  t_symbol *lst = {0};

  set_elf64_infos(&elf, map, file_name, file_size);
  if (parse_symbols64(elf, &lst))
    return EXIT_FAILURE;
  sort_default64(&lst);
  delete_duplicates_symbols(&lst);
  print_symbols64(lst);
  // print_symtab_x64(elf);
  // print_dynsym_x64(elf);
  clear_list(&lst);
  return EXIT_SUCCESS;
}
