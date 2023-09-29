#include <ft_nm.h>

void print_helper(int fd) {
  ft_printf_fd(fd, "Usage: ft_nm [option(s)] [file(s)]\n"
                   "  List symbols in [file(s)] (a.out by default).\n"
                   "  The options are:\n"
                   "    -h: Display this information\n"
                   "    -a: Display debugger-only symbols\n"
                   "    -g: Display only external symbols\n"
                   "    -u: Display only undefined symbols\n"
                   "    -r: Reverse the sense of the sort\n"
                   "    -p: Do not sort the symbols\n"
                   "ft_nm: supported targets: 86_32, x64, object files, .so\n");
}

int nm_wrapper(char *file_name) {
  uint8_t *map       = NULL;
  off_t    file_size = 0;
  char     arch      = 0;
  int      res       = 0;

  if (init(file_name, &map, &file_size, &arch))
    return EXIT_FAILURE;
  if (arch == ELFCLASS32)
    res = handle_elf32(file_name, map, file_size);
  if (arch == ELFCLASS64)
    res = handle_elf64(file_name, map, file_size);
  munmap(map, file_size);
  if (res && !file_is_stripped)
    ft_printf_fd(2, "%s: %s: file format not recognized\n", prog_name,
                 file_name);
  return res;
}
