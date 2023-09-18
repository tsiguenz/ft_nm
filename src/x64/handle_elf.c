#include <ft_nm.h>

int handle_elf64(char *file_name, uint8_t *map, off_t file_size) {
  t_elf64   elf   = {0};
  t_symbol *lst   = {0};
  char      debug = 0;

  set_elf64_infos(&elf, map, file_name, file_size);
  if (parse_symbols64(elf, &lst))
    return EXIT_FAILURE;
  sort_default64(&lst);
  delete_duplicates_symbols(&lst);
  // reverse_print_symbols64(lst, debug);
  print_symbols64(lst, debug);
  clear_list(&lst);
  return EXIT_SUCCESS;
}
