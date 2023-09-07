#include "include/test.h"

char *set_file_size_tests(void) {
  int fd = -1;
  off_t file_size = 0;
  {
    char *filename = "test/bin/print42_x64";
    set_fd(filename, &fd);
    set_file_size(filename, fd, &file_size);
    mu_assert(__FILE__ ": regular file", file_size == 15960);
    close(fd);
  }
  {
    char *filename = "test/bin/empty";
    set_fd(filename, &fd);
    mu_assert(__FILE__ ": empty file",
              set_file_size(filename, fd, &file_size) == 1);
    close(fd);
  }
  {
    char *filename = "test";
    set_fd(filename, &fd);
    mu_assert(__FILE__ ": directory",
              set_file_size(filename, fd, &file_size) == 1);
    close(fd);
  }
  return 0;
}
