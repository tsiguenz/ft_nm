#include <ft_nm.h>

int handle_elf32(char *file_name, uint8_t *map, off_t file_size) {
  t_elf32     elf = {0};
  t_symbol32 *lst = {0};

  if (set_elf32_infos(&elf, map, file_name, file_size) ||
      parse_symbols32(elf, &lst)) {
    if (file_is_stripped)
      return EXIT_SUCCESS;
    return EXIT_FAILURE;
  }
  // print_dynsym_x32(elf);
  // print_symtab_x32(elf);
  delete_duplicates_symbols32(&lst);
  // print_all_symbols(lst);
  if (!do_not_sort)
    sort_default32(&lst);
  if (undefined_only) {
    if (!reverse_sort || do_not_sort)
      print_undefined_symbols32(lst, file_name);
    else
      reverse_print_undefined_symbols32(lst, file_name);
    clear_list32(&lst);
    return EXIT_SUCCESS;
  }
  if (external_only) {
    if (!reverse_sort || do_not_sort)
      print_external_symbols32(lst, file_name);
    else
      reverse_print_external_symbols32(lst, file_name);
    clear_list32(&lst);
    return EXIT_SUCCESS;
  }
  if (!reverse_sort || do_not_sort)
    print_symbols32(lst, file_name, debugger_only);
  else
    reverse_print_symbols32(lst, file_name, debugger_only);
  clear_list32(&lst);
  return EXIT_SUCCESS;
}
