#include "include/test.h"

char *set_fd_tests(void) {
  int fd = -1;

  set_fd("test/bin/print42_x64", &fd);
  mu_assert(__FILE__ ": working", fd > -1);
  close(fd);

  set_fd("test/bin/print42___x64", &fd);
  mu_assert(__FILE__ ": not working", fd == -1);

  set_fd("test/bin/no_perm", &fd);
  mu_assert(__FILE__ ": file with no permission", fd == -1);
  return 0;
}
