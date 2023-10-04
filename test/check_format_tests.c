#include "include/test.h"

static void test_helper(char *filename, int *fd, off_t *file_size,
                        uint8_t **map) {
  set_fd(filename, fd);
  set_file_size(filename, *fd, file_size);
  set_mapped_file(*fd, *file_size, map);
}

char *check_format_tests(void) {
  int      fd        = -1;
  off_t    file_size = 0;
  uint8_t *map       = 0;

  {
    char *filename = "test/bin/ok_files/print42_x64";
    test_helper(filename, &fd, &file_size, &map);
    mu_assert(__FILE__ ": normal elf", !check_format(map, filename, file_size));
  }
  {
    char *filename = "test/bin/bad_files/elf_changed_to_ela";
    test_helper(filename, &fd, &file_size, &map);
    mu_assert(__FILE__ ": bad magic numbers (?ELF) elf",
              check_format(map, filename, file_size));
  }
  {
    char *filename = "test/bin/bad_files/42";
    test_helper(filename, &fd, &file_size, &map);
    mu_assert(__FILE__ ": file with 2 chars",
              check_format(map, filename, file_size));
  }
  return 0;
}
