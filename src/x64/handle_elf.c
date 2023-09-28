#include <ft_nm.h>

int handle_elf64(char *file_name, uint8_t *map, off_t file_size) {
  t_elf64     elf = {0};
  t_symbol64 *lst = {0};

  if (set_elf64_infos(&elf, map, file_name, file_size) ||
      parse_symbols64(elf, &lst)) {
    if (file_is_stripped)
      return EXIT_SUCCESS;
    return EXIT_FAILURE;
  }
  // print_dynsym_x64(elf);
  // print_symtab_x64(elf);
  delete_duplicates_symbols64(&lst);
  if (!do_not_sort)
    sort_default64(&lst);
  // print_all_symbols64(lst);
  if (undefined_only) {
    if (!reverse_sort || do_not_sort)
      print_undefined_symbols64(lst, file_name);
    else
      reverse_print_undefined_symbols64(lst, file_name);
    clear_list64(&lst);
    return EXIT_SUCCESS;
  }
  if (external_only) {
    if (!reverse_sort || do_not_sort)
      print_external_symbols64(lst, file_name);
    else
      reverse_print_external_symbols64(lst, file_name);
    clear_list64(&lst);
    return EXIT_SUCCESS;
  }
  if (!reverse_sort || do_not_sort)
    print_symbols64(lst, file_name, debugger_only);
  else
    reverse_print_symbols64(lst, file_name, debugger_only);
  clear_list64(&lst);
  return EXIT_SUCCESS;
}
