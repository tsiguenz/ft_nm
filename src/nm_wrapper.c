#include <ft_nm.h>

int nm_wrapper(char *file_name) {
  uint8_t *map       = NULL;
  off_t    file_size = 0;
  char     arch      = 0;
  int      res       = 0;

  if (init(file_name, &map, &file_size, &arch))
    return EXIT_FAILURE;
  if (arch == ELFCLASS32)
    res = handle_elf32(file_name, map, file_size);
  else
    res = handle_elf64(file_name, map, file_size);
  munmap(map, file_size);
  if (res && !file_is_stripped)
    ft_printf_fd(2, "%s: %s: file format not recognized\n", prog_name,
                 file_name);
  return res;
}
