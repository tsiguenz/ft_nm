#include "include/test.h"

static void test_helper(char *filename, int *fd, off_t *file_size,
                        uint8_t **map) {
  set_fd(filename, fd);
  set_file_size(filename, *fd, file_size);
  set_mapped_file(*fd, *file_size, map);
}

char *set_arch_tests(void) {
  int fd = -1;
  off_t file_size = 0;
  uint8_t *map = 0;
  char arch;

  {
    char *filename = "test/bin/print42_x64";
    test_helper(filename, &fd, &file_size, &map);
    mu_assert(__FILE__ ": 64 bits elf ret val",
              !set_arch(map, filename, &arch));
    mu_assert(__FILE__ ": 64 bits elf arch value", arch == ELFCLASS64);
  }
  {
    char *filename = "test/bin/print42_x86_32";
    test_helper(filename, &fd, &file_size, &map);
    mu_assert(__FILE__ ": 32 bits elf ret val",
              !set_arch(map, filename, &arch));
    mu_assert(__FILE__ ": 32 bits elf arch value", arch == ELFCLASS32);
  }
  {
    char *filename = "test/bin/elfclassnone";
    test_helper(filename, &fd, &file_size, &map);
    mu_assert(__FILE__ ": bad elf class ret value",
              set_arch(map, filename, &arch));
    mu_assert(__FILE__ ": bad elf class arch value", arch == ELFCLASSNONE);
  }
  {
    char *filename = "test/bin/bad_elf_class";
    test_helper(filename, &fd, &file_size, &map);
    mu_assert(__FILE__ ": another bad elf class ret value",
              set_arch(map, filename, &arch));
    mu_assert(__FILE__ ": another bad elf class arch value", arch == 0x42);
  }
  return 0;
}
