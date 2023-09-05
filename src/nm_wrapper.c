#include <ft_nm.h>

int set_fd(char *filename, int *fd) {
  *fd = open(filename, O_RDONLY);
  if (*fd < 1) {
    ft_putstr_fd(PROG_NAME ": '", 2);
    ft_putstr_fd(filename, 2);
    ft_putstr_fd("': No such file\n", 2);
    return 1;
  }
  return 0;
}

int set_file_size(int fd, off_t *file_size) {
  struct stat fs;

  if (fstat(fd, &fs) == -1) {
    ft_putstr_fd(PROG_NAME ": error: fstat fail\n", 2);
    close(fd);
    return 1;
  }
  *file_size = fs.st_size;
  return 0;
}

int set_mapped_file(int fd, off_t file_size, uint8_t **map) {
  *map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);
  if (map == MAP_FAILED) {
    ft_putstr_fd(PROG_NAME ": error: mmap fail\n", 2);
    return 1;
  }
  return 0;
}

int check_format(uint8_t *map, char *filename) {
  int magic_numbers[4] = {0x7f, 'E', 'L', 'F'};
  for (int i = 0; i < 4; i++) {
    if (map[i] != magic_numbers[i]) {
      ft_putstr_fd(PROG_NAME ": ", 2);
      ft_putstr_fd(filename, 2);
      ft_putstr_fd(": file format not recognized\n", 2);
      return 1;
    }
  }
  return 0;
}

int set_arch(uint8_t *map, char *filename, char *arch) {
  *arch = *(map + 0x4);
  if (*arch == ELFCLASSNONE || *arch > 2) {
    ft_putstr_fd(PROG_NAME ": ", 2);
    ft_putstr_fd(filename, 2);
    ft_putstr_fd(": file format not recognized\n", 2);
    return 1;
  }
  return 0;
}

int nm_wrapper(char *filename) {
  int fd;
  uint8_t *map = NULL;
  off_t file_size = 0;
  char arch;

  if (set_fd(filename, &fd) || set_file_size(fd, &file_size) ||
      set_mapped_file(fd, file_size, &map) || check_format(map, filename) ||
      set_arch(map, filename, &arch))
    return 1;
  ft_printf("arch = %d\n", arch);
  //	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)map;
  //  Elf64_Shdr *shdr = (Elf64_Shdr *)map + ehdr->e_shoff;
  //  (void)ehdr;
  //  (void)shdr;
  // ft_printf("%d\n", section->sh_type);
  //  for (int i = 0; i < fs.st_size; i++)
  //    write(1, &map[i], 1);
  munmap(map, file_size);
  return (0);
}
