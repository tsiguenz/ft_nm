#include "include/test.h"

char *set_fd_tests(void) {
  int fd = -1;

  set_fd("test/bin/print42_x64", &fd);
  mu_assert(__FILE__ ": set_fd() working", fd > -1);
  close(fd);

  set_fd(__FILE__ ": test/bin/print42___x64", &fd);
  mu_assert("set_fd() not working", fd == -1);
  return 0;
}
