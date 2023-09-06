#include <ft_nm.h>

int set_fd(char *filename, int *fd) {
  *fd = open(filename, O_RDONLY);
  if (*fd < 1) {
    ft_printf_fd(2, "%s: '%s': No such file\n", PROG_NAME, filename);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int set_file_size(char *filename, int fd, off_t *file_size) {
  struct stat fs;

  if (fstat(fd, &fs) == -1) {
    ft_putstr_fd(PROG_NAME ": error: fstat fail\n", 2);
    close(fd);
    return EXIT_FAILURE;
  }
  if (S_ISDIR(fs.st_mode)) {
    ft_printf_fd(2, "%s: Warning: '%s' is a directory\n", PROG_NAME, filename);
    return EXIT_FAILURE;
  }
  *file_size = fs.st_size;
  return EXIT_SUCCESS;
}

int set_mapped_file(int fd, off_t file_size, uint8_t **map) {
  *map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  close(fd);
  if (map == MAP_FAILED) {
    ft_putstr_fd(PROG_NAME ": error: mmap fail\n", 2);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int check_format(uint8_t *map, char *filename) {
  int magic_numbers[4] = {0x7f, 'E', 'L', 'F'};
  for (int i = 0; i < 4; i++) {
    if (map[i] != magic_numbers[i]) {
      ft_printf_fd(2, "%s: '%s': File format not recognized\n", PROG_NAME,
                   filename);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

// doesn't check if arch byte was changed
int set_arch(uint8_t *map, char *filename, char *arch) {
  *arch = *(map + 0x4);
  if (*arch == ELFCLASSNONE || *arch > 2) {
    ft_printf_fd(2, "%s: '%s': File format not recognized\n", PROG_NAME,
                 filename);
    return EXIT_SUCCESS;
  }
  return EXIT_SUCCESS;
}

int init(char *filename, uint8_t **map, off_t *file_size, char *arch) {
  int fd = 0;

  if (set_fd(filename, &fd) || set_file_size(filename, fd, file_size) ||
      set_mapped_file(fd, *file_size, map) || check_format(*map, filename) ||
      set_arch(*map, filename, arch)) {
    if (map)
      munmap(map, *file_size);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
