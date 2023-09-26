#include <ft_nm.h>

int handle_elf64(char *file_name, uint8_t *map, off_t file_size) {
  t_elf64   elf   = {0};
  t_symbol *lst   = {0};
  char      debug = 0;

  (void) debug;
  if (set_elf64_infos(&elf, map, file_name, file_size) ||
      parse_symbols64(elf, &lst)) {
    if (file_is_stripped)
      return EXIT_SUCCESS;
    return EXIT_FAILURE;
  }
  //	print_all_symbols_name(lst);
  //  print_dynsym_x64(elf);
  //  print_symtab_x64(elf);
  delete_duplicates_symbols(&lst);
  sort_default64(&lst);
  print_symbols64(lst, file_name, debug);
  //  reverse_print_symbols64(lst, debug);
  clear_list(&lst);
  return EXIT_SUCCESS;
}
