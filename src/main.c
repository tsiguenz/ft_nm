#ifndef __IS_TEST__

#include <ft_nm.h>

int main(int ac, char **av) {
  if (ac != 2) {
    write(2, "Bad number of arguments\n", 23);
    return (1);
  }
  int fd = open(av[1], O_RDONLY);
  if (fd < 1) {
    write(2, "error: ", 7);
    write(2, av[1], ft_strlen(av[1]));
    write(2, ": No such file or directory\n", 28);
    return (1);
  }
  ft_printf("fd = %d\n", fd);
  return (0);
}

#endif // __IS_TEST__
