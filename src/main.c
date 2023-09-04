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

  struct stat fs;
  if (fstat(fd, &fs) == -1) {
    write(2, "error: fstat fail\n", 18);
    return (1);
  }
  char *addr = mmap(NULL, fs.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (addr == MAP_FAILED) {
    write(2, "error: mmap fail\n", 17);
    return (1);
  }
  for (int i = 0; i < fs.st_size; i++)
    write(1, &addr[i], 1);
  munmap(addr, fs.st_size);
  close(fd);
  return (0);
}

#endif // __IS_TEST__
